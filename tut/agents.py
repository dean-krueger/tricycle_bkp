from cyclus.agents import Facility
import cyclus.typesystem as ts

class FusionReactor(Facility):
    """Make a new Fusion Reactor Facility"""


############################################################################################
#                                Material Buffers                                          #
############################################################################################

    # the reserve and excess tritium inventory
    tritium_reserve = ts.ResBufMaterialInv()

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
        self.entry_times = []
        
        
############################################################################################
#                                 Tick and Tock                                            #
############################################################################################


    def tick(self):

        print("Timestep: ", self.context.time)
        if self.context.time == self.enter_time:
            self.startup(self.startup_inventory, self.reserve_inventory)
            #Print some Diagnostics:
            print("Tritium in the Core: ", self.tritium_core.quantity, " (kg)")
            print("Tritium in Reserve Inventory: ",  self.tritium_reserve.quantity, " (kg)\n")

        self.breed_tritium(1.05, 55.8)
      


    def tock(self):
        #Print some Diagnostics:
        print("Tritium in the Core: ", self.tritium_core.quantity, " (kg)")
        print("Tritium in Reserve Inventory: ",  self.tritium_reserve.quantity, " (kg)\n")
        

############################################################################################
#                                Fusion Functions                                          #
############################################################################################
    
    def breed_tritium(self, TBR, burn_rate):
        seconds_per_year = 31536000
        fuel_usage = burn_rate * (self.fusion_power / 1000) / seconds_per_year * self.context.dt  #[kg/timestep]
        
        print("Fuel Usage: ", fuel_usage)

        #Pull the fuel out of the core and remove fuel_usage from it:
        fuel = self.tritium_core.pop()
        burned_fuel = fuel.extract_qty(fuel_usage)

        #Add the new tritium to the fuel:
        recipe = self.context.get_recipe(self.fuel_inrecipe)
        bred_fuel = ts.Material.create(self, TBR*fuel_usage, recipe)
        fuel.absorb(bred_fuel)
        self.tritium_core.push(fuel)
        

    def startup(self, startup_inventory, reserve_inventory):
        #move the startup tritium inventory into the core:
        recipe = self.context.get_recipe(self.fuel_inrecipe)
        
        initial_inventory = ts.Material.create(self,startup_inventory, recipe)
        self.tritium_core.push(initial_inventory)

        reserve = ts.Material.create(self, reserve_inventory, recipe)
        self.tritium_reserve.push(reserve)

        
           
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