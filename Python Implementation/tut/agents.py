from cyclus.agents import Facility
import cyclus.typesystem as ts
import inspect
import math

class FusionReactor(Facility):
    """Make a new Fusion Reactor Facility"""


############################################################################################
#                                Material Buffers                                          #
############################################################################################

    # the reserve and excess tritium inventory
    tritium_storage = ts.ResBufMaterialInv()

    # tritium currently stored "in the reactor"
    tritium_core =  ts.ResBufMaterialInv()

    # blanket material currently in the blanket
    active_blanket = ts.ResBufMaterialInv()

    # blanket material stored outside the blanket
    inactive_blabket = ts.ResBufMaterialInv()

    # the Helium-3 which results from decay of Tritium
    helium_storage = ts.ResBufMaterialInv()


############################################################################################
#                                State Variables                                           #
############################################################################################
    
    fusion_power = ts.Double(
        doc = "Fusion power of the reactor in MW",
        tooltip = "Fusion power of the reactor in MW",
        units = "MW",
        uilabel = "Fusion Power"
    )
   
    TBR = ts.Double(
        doc = "Achievable system tritium breeding ratio",
        tooltip = "Achievable system tritium breeding ratio",
        units = "non-dimensional",
        uilabel = "Tritium Breeding Ratio"
    )
    
    reserve_inventory = ts.Double(
        doc = "Minimum tritium inventory to hold in reserve in case of tritium recovery system failure",
        tooltip = "Minimum tritium inventory to hold in reserve in case of tritium recovery system failure",
        units = "kg",
        uilabel = "Reserve Inventory"
    )
    
    startup_inventory = ts.Double(
        doc = "Tritium inventory required to start reactor",
        tooltip = "Tritium inventory required to start reactor",
        units = "kg",
        uilabel = "Start-up Inventory"
    )

    fuel_incommod = ts.String(
        doc = "Fresh fuel commodity",
        tooltip = "Name of fuel commodity requested",
        uilabel = "Input Commodity"
    )

    fuel_inrecipe = ts.String(
        doc = "Fresh fuel recipe",
        tooltip = "Fresh fuel recipe",
        uilabel = "Input commodity recipe"
    )
    '''
    blanket_incommods = ts.String(
        doc = "Blanket commodity",
        tooltip = "Name of blanket material requested",
        uilabel = "Input Commodity",
    )

    blanket_inrecipes = ts.String(
        doc = "Fresh blanket material recipe",
        tooltip = "Fresh blanket maetrial recipe",
        uilabel = "Input commodity recipe",
    )

    fuel_purchase_frequency = ts.Int(
        doc = "Frequency with which fuel is purchased",
        tooltip = "Frequency with which fuel is purchased",
        units = "timesteps",
        uilabel = "Fuel Purchase Frequency",
    )

    availability_factor = ts.Double(
        doc = "Availability factor of the reactor",
        tooltip = "Availability factor of the reactor",
        units = "non-dimensional",
        default = 1.0,
        uilabel = "Availability Factor",
    )
    '''

############################################################################################
#                                 Initialization                                           #
############################################################################################


    def __init__(self, ctx):
        """Agents that have an init method must accept a context and must call super first thing!"""
        super().__init__(ctx)
        self.burn_rate = 55.8 #[kg/yr*GW]
        self.operational = True
        
############################################################################################
#                                 Tick and Tock                                            #
############################################################################################


    def tick(self):
        print("Timestep: ", self.context.time)
        if self.context.time == self.enter_time:
            self.startup(self.startup_inventory, self.reserve_inventory)
        else:
            #Operate the Reactor    
            self.operate_reactor(self.TBR, self.burn_rate)
    
            #Decay:
            self.decay_inventory(self.tritium_core)
            self.decay_inventory(self.tritium_storage)

    def tock(self):
        #Print some Diagnostics:
        print("Tritium in the Core: ", self.tritium_core.quantity, " (kg)")
        print("Tritium in Storage: ",  self.tritium_storage.quantity, " (kg)")
        print("Helium-3 in Storage: ",  self.helium_storage.quantity, " (kg)\n")
    

############################################################################################
#                                Fusion Functions                                          #
############################################################################################
    
    def decay_inventory(self, inventory):
        mat = inventory.pop()
        mat.decay(self.context.time)
        inventory.push(mat)


    def extract_helium(self, mat):
        c = mat.comp()
        #print("Material Composition: ", c)
        if 20030000 in c:

            #print(c[20030000])
            he3 = mat.extract_comp(c[20030000], {20030000:1})
            self.helium_storage.push(he3)

    def operate_reactor(self, TBR, burn_rate):
        '''
        Tritium is now decaying, so the composition of the tritium in storage AND in the core is changing over time:

        1. Go through and make sure that we handle breeding correctly wrt the changing composition
        2. Change the concept of "tritium in core" to the mass of the actual tritium, NOT just the total mass of the composition
        3. Double check that when we create new tritium it is "fresh" (100% tritium)
        4. Ensure that the core and storage compositions are the same

        Note: since we're currently just moving the quantity around, the core is getting super depleteed

        '''

        #Create some constants for use later
        seconds_per_year = 31536000
        fuel_usage = burn_rate * (self.fusion_power / 1000) / seconds_per_year * self.context.dt  #[kg/timestep] 
        bred_fuel_qty = fuel_usage*TBR
        recipe = self.context.get_recipe(self.fuel_inrecipe)

        #Make a new Table to record reactor power, and tritium reserves
        d = self.context.new_datum("ReactorData")
        d.add_val("AgentID", value=self.id, type='int')
        d.add_val("Time", value=self.context.time, type='int')

        
        #if more fuel gets created than is burned, add the difference to the storage
        if bred_fuel_qty >= fuel_usage:

            #Set the operational status of the reactor
            self.operational = True
            
            #make new fuel. The if statement above ensures that this will always be positive (or zero)
            bred_fuel = ts.Material.create(self, bred_fuel_qty-fuel_usage, recipe)

            #pop all the fuel out and add it together
            storage_fuel = self.tritium_storage.pop()
            core_fuel = self.tritium_core.pop()

            storage_fuel.absorb(core_fuel)

            #rename the fuel so it's easier to read:
            fuel = storage_fuel

            #pull out the tritium used in the fusion reactor (change the composition):
            print("Fuel Composition before extraction: ", fuel.comp())
            self.extract_helium(fuel)
            print("Fuel Composition after extraction: ", fuel.comp())
            #add the bred fuel to the depleted fuel:
            fuel.absorb(bred_fuel)

            #pull the amount of fuel that needs to go back into the core out
            homoginized_core_fuel = fuel.extract_qty(self.startup_inventory)


            #add the core fuel back to the core
            self.tritium_core.push(homoginized_core_fuel)

            #add the rest of the fuel back to storage
            self.tritium_storage.push(fuel)

            #Reactor Produces Full Power this timestep
            d.add_val("Status", value="Online", type='std::string')
            d.add_val("Power Produced", value=self.fusion_power, type='double')
            
        else:
            
            #We've used more fuel than we made, so we eneed to remove the difference from the core, and then replenish the core with what's in storage:
            
            '''check whether self.operational is necessary'''
            fuel_qty_to_remove = (fuel_usage - bred_fuel_qty)*self.operational




            #print("Composition of the Core After Extraction: ", core_fuel.comp())

            # first, since there's been a decay: extract the helium from the fuel in storage to get an accourate account of how much tritium is there
            storage_fuel = self.tritium_storage.pop()

            #pull out the fuel in the core and extract the helium
            core_fuel = self.tritium_core.pop()
            
            #He-3 separation
            print("Composition Before Extraction: ", storage_fuel.comp())
            self.extract_helium(storage_fuel)
            print("Composition After Extraction: ", storage_fuel.comp())

            #He-3 separation
            self.extract_helium(core_fuel)

            used_fuel = core_fuel.extract_qty(fuel_qty_to_remove)

            #Calculate how much fuel we need to move
            core_deficit = self.startup_inventory - core_fuel.quantity

            #check that there's enough tritium in storage:
            if storage_fuel.quantity > core_deficit:
                
                #set the operational status of the reactor
                self.operational = True

                #separate the right amount of fuel from storage fuel
                fuel_to_core = storage_fuel.extract_qty(core_deficit)

                #add fuel_to_core to core_fuel
                core_fuel.absorb(fuel_to_core)

                #Put the core fuel back in the core, and the storage fuel back in storage
                self.tritium_core.push(core_fuel)
                self.tritium_storage.push(storage_fuel)

                #delete the used fuel to prevent memory issues (not sure how big of a problem this actually is)
                del used_fuel
                
                #Reactor produces full power this timestep
                d.add_val("Status", value="Online", type='std::string')
                d.add_val("Power Produced", value=self.fusion_power, type='double')


            else:
                #We no longer have enough fuel to keep the reactor operating, so we need to "shut down" until we can order more fuel
                self.operational = False

                #Put the core fuel back in the core, and the storage fuel back in storage
                self.tritium_core.push(core_fuel)
                self.tritium_storage.push(storage_fuel)

                #Reactor produces no power this timestep
                d.add_val("Status", value="Shut Down", type='std::string')
                d.add_val("Power Produced", value=0.0, type='double')
                


    def startup(self, startup_inventory, reserve_inventory):
        #move the startup tritium inventory into the core:
        recipe = self.context.get_recipe(self.fuel_inrecipe)
        
        initial_inventory = ts.Material.create(self,startup_inventory, recipe)
        
        self.tritium_core.push(initial_inventory)

        reserve = ts.Material.create(self, reserve_inventory, recipe)
        self.tritium_storage.push(reserve)

        
           
############################################################################################
#                                 DRE Functions                                            #
############################################################################################

    '''
    def get_material_requests(self):
        #Buy Strategy: If there is less Tritium in the system than we started with, buy at least enough to restock
        system_deficit = self.startup_inventory + self.reserve_inventory - self.tritium_core.quantity - self.tritium_storage.quantity

        print("System Deficit: ", system_deficit)

        #Material Target:
        recipe = self.context.get_recipe(self.fuel_inrecipe)
        target = ts.Material.create_untracked(system_deficit, recipe)
        
        #Define Commodity Dict:
        commod = {self.fuel_incommod : target}

        #Define Portfolio:
        if (system_deficit > 0):
            ports = {"commodities": commod, "constraints" : system_deficit}
        else:
            ports = {}
        
        return ports
    """
    def get_material_bids(self, requests):
        reqs = requests[self.outcommod]
        #bids = []
        bids = [req for req in reqs]

        port = {"bids" : bids, "constraints" : self.output.quantity}

        return port
    """
    
    def get_material_trades(self, trades):
        responses = {}
        for trade in trades:
            mat = ts.Material.create(self, trade.amt, trade.request.target.comp())
            responses[trade] = mat
        return responses
    
    
    def accept_material_trades(self, responses):
        #Pull the tritium in storage out:
        storage_fuel = self.tritium_storage.pop()
        
        #Mix the newly acquired tritium with what was in storage
        for mat in responses.values():
            print("Hello")
            storage_fuel.absorb(mat)
        
        #Put the storage fuel back
        self.tritium_storage.push(storage_fuel)
    '''