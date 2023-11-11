from cyclus.agents import Facility
import cyclus.typesystem as ts
import inspect

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


############################################################################################
#                                State Variables                                           #
############################################################################################
    
    fusion_power = ts.Double(
        doc = "Fusion power of the reactor in MW",
        tooltip = "Fusion power of the reactor in MW",
        units = "MW",
        uilabel = "Fusion Power",
    )
   
    TBR = ts.Double(
        doc = "Achievable system tritium breeding ratio",
        tooltip = "Achievable system tritium breeding ratio",
        units = "non-dimensional",
        uilabel = "Tritium Breeding Ratio",
    )
    
    reserve_inventory = ts.Double(
        doc = "Minimum tritium inventory to hold in reserve in case of tritium recovery system failure",
        tooltip = "Minimum tritium inventory to hold in reserve in case of tritium recovery system failure",
        units = "kg",
        uilabel = "Reserve Inventory",
    )
    
    startup_inventory = ts.Double(
        doc = "Tritium inventory required to start reactor",
        tooltip = "Tritium inventory required to start reactor",
        units = "kg",
        uilabel = "Start-up Inventory",
    )

    fuel_incommod = ts.String(
        doc = "Fresh fuel commodity",
        tooltip = "Name of fuel commodity requested",
        uilabel = "Input Commodity",
    )

    fuel_inrecipe = ts.String(
        doc = "Fresh fuel recipe",
        tooltip = "Fresh fuel recipe",
        uilabel = "Input commodity recipe",
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
            print(dir(ts.Material))
        #Operate the Reactor 
        self.operate_reactor(self.TBR, self.burn_rate)
        
        #Decay:
        self.decay_inventory(self.tritium_core)
        self.decay_inventory(self.tritium_storage)

    def tock(self):
        #Print some Diagnostics:
        print("Tritium in the Core: ", self.tritium_core.quantity, " (kg)")
        print("Tritium in Storage: ",  self.tritium_storage.quantity, " (kg)\n")
    

############################################################################################
#                                Fusion Functions                                          #
############################################################################################
    
    def decay_inventory(self, inventory):
        mat = inventory.pop()
        decayed_mat = mat.decay(self.context.time)
        if decayed_mat is not None:
            inventory.push(decayed_mat)
        else:
            print(mat.comp())
            inventory.push(mat)
            

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
        datum = self.context.new_datum("ReactorData")
        datum.add_val(field="AgentID", value=self.id, type=ts.INT)
        datum.add_val(field="Time", value=self.context.time, type=ts.INT)
        datum.add_val(field="TEST_1", value="TEST_1", type=ts.STRING)
        datum.add_val(field="TEST_2", value="TEST_2", type=ts.STRING)


        #if more fuel gets created than is burned, add the difference to the storage
        if bred_fuel_qty >= fuel_usage:
            '''
            This is currently not taking the spent fuel out of stroage and adding the new fuel, it's just adding new fuel.
            This wasn't a problem before, but now that we're decaying we have to be careful with the composition change.
            '''
            
            self.operational = True
            #make new fuel. The if statement above ensures that this will always be positive (or zero)
            bred_fuel = ts.Material.create(self, bred_fuel_qty-fuel_usage, recipe)
            
            #pop all the fuel out and add it together
            storage_fuel = self.tritium_storage.pop()
            core_fuel = self.tritium_core.pop()
            fuel = storage_fuel.absorb(core_fuel)

            #pull out the tritium used in the fusion reactor (change the composition):
            
            depleted_fuel = fuel.extract_comp(fuel_usage, recipe, 1)
            print("Hello")
            #add the bred fuel to the depleted fuel:
            replenished_fuel = depleted_fuel.absorb(bred_fuel)

            homoginized_core_fuel = replenished_fuel.extract_qty(self.startup_inventory)
            self.tritium_core.push(homoginized_core_fuel)

            #add the fuel back to storage
            self.tritium_storage.push(replenished_fuel)


            
            #Reactor Produces Full Power this timestep
            datum.add_val(field="Status", value="Online", type=ts.STRING)
            datum.add_val(field="Power Produced", value=self.fusion_power, type=ts.DOUBLE)

        else:
            self.operational = True
            #We've used more fuel than we made, so we eneed to remove the difference from the core, and then replenish the core with what's in storage:
            fuel_qty_to_remove = fuel_usage - bred_fuel_qty

            #first check that there's enough fuel in storage:
            if self.tritium_storage.quantity > fuel_qty_to_remove:
                core_fuel = self.tritium_core.pop()
                used_fuel = core_fuel.extract_qty(fuel_qty_to_remove)
            
                #replenish the core by feeding it tritium from storage

                #Calculate how much fuel we need to move
                core_deficit = self.startup_inventory - core_fuel.quantity

                #pull fuel out of storage
                storage_fuel = self.tritium_storage.pop()

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
                datum.add_val(field="Status", value="Online", type=ts.STRING)
                datum.add_val(field="Power Produced", value=self.fusion_power, type=ts.DOUBLE)


            else:
                
                #We no longer have enough fuel to keep the reactor operating, so we need to "shut down" until we can order more fuel
                self.operational = False
                #Reactor produces no power this timestep
                datum.add_val(field="Status", value="Shut Down", type=ts.STRING)
                datum.add_val(field="Power Produced", value=0.0, type=ts.DOUBLE)
                


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
        #Buy Strategy: request as many fuel elements as the facility can hold
        request_qty = self.capacity - self.inventory.quantity - self.output.quantity
              
        print("Request Quantity: ", request_qty)
        print("Current Inventory: ", self.inventory.quantity)
        print("Current Output: ", self.output.quantity, "\n")

        #Material Target:
        recipe = self.context.get_recipe(self.inrecipe)
        target = ts.Material.create_untracked(request_qty, recipe)

        #Define Commodity Dict:
        commod = {self.incommod : target}

        #Define Portfolio:
        ports = {"commodities": commod, "constraints" : request_qty}
        
        return ports
    
    def get_material_bids(self, requests):
        reqs = requests[self.outcommod]
        #bids = []
        bids = [req for req in reqs]

        port = {"bids" : bids, "constraints" : self.output.quantity}

        return port
    
    def get_material_trades(self, trades):
        responses = {}
        for trade in trades:
            mat = ts.Material.create(self, trade.amt, trade.request.target.comp())
            responses[trade] = mat
        return responses
    
    def accept_material_trades(self, responses):
        for mat in responses.values():
            self.input.push(mat)

    '''