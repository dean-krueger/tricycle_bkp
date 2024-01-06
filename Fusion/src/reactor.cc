#include "reactor.h"

namespace fusion {

//-----------------------------------------------------------//
//                       Constructor                         //
//-----------------------------------------------------------//
Reactor::Reactor(cyclus::Context* ctx) : cyclus::Facility(ctx) {}


std::string Reactor::str() {
  return Facility::str();
}

//-----------------------------------------------------------//
//                      Tick and Tock                        //
//-----------------------------------------------------------//
void Reactor::Tick() {
  std::cout << "Timestep: " << context()->time() <<std::endl;
  if(context()->time() == enter_time()){
    Startup(startup_inventory, reserve_inventory);
  }

  
  //Run the Reactor for one timestep:
  OperateReactor(TBR);

  //Decay both our inventories
  DecayInventory(tritium_storage);
  DecayInventory(tritium_core);


}

void Reactor::Tock() {
  std::cout << "Tritium in Core: " << tritium_core.quantity() << std::endl;
  std::cout << "Tritium in Storage: " << tritium_storage.quantity() << std::endl;
  std::cout << "Helium in Storage: " << helium_storage.quantity() << std::endl << std::endl;

}

//-----------------------------------------------------------//
//                     Fusion Functions                      //
//-----------------------------------------------------------//

void Reactor::Startup(double startup_inventory, double reserve_inventory){ 
  //For now, we conjure some tritium from thin air and put it in our reactor. Later we'll fix this
  //I think we may get rid of this function later and replace it with a DRE step, so for now let's
  //Just use it to load the reactor on the first timestep.


  //Make the appropriate composition (we can't trust context()->GetRecipe())?
  cyclus::CompMap T;
  T[10030000] = 1;

  //Create the Tritium
  cyclus::Material::Ptr initial_core = cyclus::Material::Create(this, startup_inventory, cyclus::Composition::CreateFromAtom(T));
  cyclus::Material::Ptr initial_reserve = cyclus::Material::Create(this, reserve_inventory, cyclus::Composition::CreateFromAtom(T));
  
  //Load the tritium in reserve and core inventories.
  tritium_core.Push(initial_core);
  tritium_storage.Push(initial_reserve);
}

void Reactor::DecayInventory(cyclus::toolkit::ResBuf<cyclus::Material> inventory){
  cyclus::Material::Ptr mat = inventory.Pop();  
  
  //Do we want to make this Decay(context()->time()-entrytime())
  //for reactors which come online at later timesteps?
  mat->Decay(context()->time());
  inventory.Push(mat);
}

void Reactor::ExtractHelium(cyclus::Material::Ptr mat){
  cyclus::CompMap c = mat->comp()->atom();
  cyclus::compmath::Normalize(&c,mat->quantity());

  cyclus::CompMap He3;
  He3[20030000] = 1;
  

  cyclus::Material::Ptr helium = mat->ExtractComp(c[20030000], cyclus::Composition::CreateFromAtom(He3));
  helium_storage.Push(helium);
}

void Reactor::Record(std::string status, double power){
    context()
      ->NewDatum("ReactorData")
      ->AddVal("AgentId", id())
      ->AddVal("Time", context()->time())
      ->AddVal("Status", status)
      ->AddVal("Power", power)
      ->Record();
}

void Reactor::OperateReactor(double TBR, double burn_rate){
  int seconds_per_year = 31536000;
  double fuel_usage = burn_rate * (fusion_power / 1000) / seconds_per_year * context()->dt();
  double bred_fuel_qty = fuel_usage*TBR;
  
  cyclus::CompMap T;
  T[10030000] = 1;
  cyclus::Composition::Ptr recipe = cyclus::Composition::CreateFromAtom(T); 

  //If more fuel is bred than burned, add the difference to storage
  if(bred_fuel_qty >= fuel_usage){
    
    /*The way this is written technically allows for a reactor with TBR > 1
      to run even in a situation where there's very little tritium in the
      core and high burnup. This should be addressed in Version 1, and
      maybe sooner...*/


    //"breed" the new Tritium
    cyclus::Material::Ptr bred_fuel = cyclus::Material::Create(this, bred_fuel_qty-fuel_usage, recipe);
    
    //Pull all the fuel out and combine it
    cyclus::Material::Ptr storage_fuel = tritium_storage.Pop();
    cyclus::Material::Ptr core_fuel = tritium_core.Pop();
    storage_fuel->Absorb(core_fuel);

    //Extract the He-3 from the fuel:
    ExtractHelium(storage_fuel);

    //Add the new, bred fuel to the mix:
    storage_fuel->Absorb(bred_fuel);

    cyclus::Material::Ptr homoginized_core_fuel = storage_fuel->ExtractComp(startup_inventory, recipe);

    //Add all the fuel back to the core/storage
    tritium_core.Push(homoginized_core_fuel);
    tritium_storage.Push(storage_fuel);   

    Reactor::Record("Online", fusion_power);
    
  }
  //If more fuel is burned than bred, remove the difference from the core, and then replenish the core from storage
  else{
    //Calculate how much fuel we need to remove
    double fuel_qty_to_remove = fuel_usage - bred_fuel_qty;
    
    //Pull all the fuel out
    cyclus::Material::Ptr storage_fuel = tritium_storage.Pop();
    cyclus::Material::Ptr core_fuel = tritium_core.Pop();

    //Extract Helium:
    ExtractHelium(storage_fuel);
    ExtractHelium(core_fuel);

    /*This part of the function got hacked together a little bit, and doesn't quite behave like I want it to:
        I need to make it go all the way until there actually isn't enough fuel to run for one more timestep,
        whereas right now it's going until the timestep before that and then throwing in the towel. It's also
        really sloppy, which I don't love. Fix this in the future!*/

    double future_deficit = startup_inventory - (core_fuel->quantity() - fuel_qty_to_remove);

    //test that there's at least enough tritium in the system to start-up the reactor
    if(((storage_fuel->quantity() + core_fuel->quantity()) > startup_inventory) && (storage_fuel->quantity() > future_deficit)){
       //Don't need to worry about deleting used_fuel since it'll go away when it goes out of scope

          
      cyclus::Material::Ptr used_fuel = core_fuel->ExtractQty(fuel_qty_to_remove); 
      double core_deficit = startup_inventory - core_fuel->quantity(); 
      cyclus::Material::Ptr fuel_to_core = storage_fuel->ExtractQty(core_deficit);

    
      //Take the difference out of storage and put it into the core

      //Once again, absorb is identified as the culpret
      core_fuel->Absorb(fuel_to_core);
      
      //Put the fuel back
      tritium_core.Push(core_fuel);
      tritium_storage.Push(storage_fuel);

      Reactor::Record("Online", fusion_power);
    }
    else{
      //We don't have enough fuel to replenish the core, so we shutdown and leave things as they are


      /*we want the behavior of this reactor to be:
        if not enough fuel:
          Shutdown
        if Shutdown:
          don't sell
          require startup
          record that we're shutdown
          
        to achieve this:
          modify startup function to load fuel from reserve
            move startup to tock?
          create a bool "operational"
            should be True while there's enough fuel
                      False when there's not enough
          make OperateReactor move all the fuel from the core to storage when there's a shutdown
          modify DRE functions to not sell while shutdown (???)
          */
      tritium_core.Push(core_fuel);
      tritium_storage.Push(storage_fuel);

      Reactor::Record("Shut-down", 0);
    }
  }

}

// WARNING! Do not change the following this function!!! This enables your
// archetype to be dynamically loaded and any alterations will cause your
// archetype to fail.
extern "C" cyclus::Agent* ConstructReactor(cyclus::Context* ctx) {
  return new Reactor(ctx);
}

}  // namespace fusion
