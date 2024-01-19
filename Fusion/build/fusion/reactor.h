
#line 1 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
#ifndef CYCLUS_FUSION_REACTOR_H_
#define CYCLUS_FUSION_REACTOR_H_

#include <string>

#include "cyclus.h"

namespace fusion {

/// @class Reactor
///
/// This Facility is intended
/// as a skeleton to guide the implementation of new Facility
/// agents.
/// The Reactor class inherits from the Facility class and is
/// dynamically loaded by the Agent class when requested.
///
/// @section intro Introduction
/// Place an introduction to the agent here.
///
/// @section agentparams Agent Parameters
/// Place a description of the required input parameters which define the
/// agent implementation.
///
/// @section optionalparams Optional Parameters
/// Place a description of the optional input parameters to define the
/// agent implementation.
///
/// @section detailed Detailed Behavior
/// Place a description of the detailed behavior of the agent. Consider
/// describing the behavior at the tick and tock as well as the behavior
/// upon sending and receiving materials and messages.
class Reactor : public cyclus::Facility  {
 public:
  /// Constructor for Reactor Class
  /// @param ctx the cyclus context for access to simulation-wide parameters
  explicit Reactor(cyclus::Context* ctx);

  /// The Prime Directive
  /// Generates code that handles all input file reading and restart operations
  /// (e.g., reading from the database, instantiating a new object, etc.).
  /// @warning The Prime Directive must have a space before it! (A fix will be
  /// in 2.0 ^TM)

  virtual void InitFrom(fusion::Reactor* m) {
    cyclus::Facility::InitFrom(m);
    int rawcycpp_shape_fusion_power[1] = {-1};
    cycpp_shape_fusion_power = std::vector<int>(rawcycpp_shape_fusion_power, rawcycpp_shape_fusion_power + 1);
    int rawcycpp_shape_TBR[1] = {-1};
    cycpp_shape_TBR = std::vector<int>(rawcycpp_shape_TBR, rawcycpp_shape_TBR + 1);
    int rawcycpp_shape_reserve_inventory[1] = {-1};
    cycpp_shape_reserve_inventory = std::vector<int>(rawcycpp_shape_reserve_inventory, rawcycpp_shape_reserve_inventory + 1);
    int rawcycpp_shape_startup_inventory[1] = {-1};
    cycpp_shape_startup_inventory = std::vector<int>(rawcycpp_shape_startup_inventory, rawcycpp_shape_startup_inventory + 1);
    int rawcycpp_shape_buy_quantity[1] = {-1};
    cycpp_shape_buy_quantity = std::vector<int>(rawcycpp_shape_buy_quantity, rawcycpp_shape_buy_quantity + 1);
    int rawcycpp_shape_fuel_incommod[1] = {-1};
    cycpp_shape_fuel_incommod = std::vector<int>(rawcycpp_shape_fuel_incommod, rawcycpp_shape_fuel_incommod + 1);
    int rawcycpp_shape_blanket_size[1] = {-1};
    cycpp_shape_blanket_size = std::vector<int>(rawcycpp_shape_blanket_size, rawcycpp_shape_blanket_size + 1);
    int rawcycpp_shape_blanket_incommod[1] = {-1};
    cycpp_shape_blanket_incommod = std::vector<int>(rawcycpp_shape_blanket_incommod, rawcycpp_shape_blanket_incommod + 1);
    int rawcycpp_shape_blanket_inrecipe[1] = {-1};
    cycpp_shape_blanket_inrecipe = std::vector<int>(rawcycpp_shape_blanket_inrecipe, rawcycpp_shape_blanket_inrecipe + 1);
    int rawcycpp_shape_tritium_core[2] = {-1, -1};
    cycpp_shape_tritium_core = std::vector<int>(rawcycpp_shape_tritium_core, rawcycpp_shape_tritium_core + 2);
    int rawcycpp_shape_tritium_storage[2] = {-1, -1};
    cycpp_shape_tritium_storage = std::vector<int>(rawcycpp_shape_tritium_storage, rawcycpp_shape_tritium_storage + 2);
    int rawcycpp_shape_helium_storage[2] = {-1, -1};
    cycpp_shape_helium_storage = std::vector<int>(rawcycpp_shape_helium_storage, rawcycpp_shape_helium_storage + 2);
    int rawcycpp_shape_blanket[2] = {-1, -1};
    cycpp_shape_blanket = std::vector<int>(rawcycpp_shape_blanket, rawcycpp_shape_blanket + 2);
    fusion_power = m->fusion_power;
    TBR = m->TBR;
    reserve_inventory = m->reserve_inventory;
    startup_inventory = m->startup_inventory;
    buy_quantity = m->buy_quantity;
    fuel_incommod = m->fuel_incommod;
    blanket_size = m->blanket_size;
    blanket_incommod = m->blanket_incommod;
    blanket_inrecipe = m->blanket_inrecipe;
    tritium_core.capacity(m->tritium_core.capacity());
    tritium_storage.capacity(m->tritium_storage.capacity());
    helium_storage.capacity(m->helium_storage.capacity());
    blanket.capacity(m->blanket.capacity());
  };
#line 46 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

  virtual void InitFrom(cyclus::QueryableBackend* b) {
    cyclus::Facility::InitFrom(b);
    int rawcycpp_shape_fusion_power[1] = {-1};
    cycpp_shape_fusion_power = std::vector<int>(rawcycpp_shape_fusion_power, rawcycpp_shape_fusion_power + 1);
    int rawcycpp_shape_TBR[1] = {-1};
    cycpp_shape_TBR = std::vector<int>(rawcycpp_shape_TBR, rawcycpp_shape_TBR + 1);
    int rawcycpp_shape_reserve_inventory[1] = {-1};
    cycpp_shape_reserve_inventory = std::vector<int>(rawcycpp_shape_reserve_inventory, rawcycpp_shape_reserve_inventory + 1);
    int rawcycpp_shape_startup_inventory[1] = {-1};
    cycpp_shape_startup_inventory = std::vector<int>(rawcycpp_shape_startup_inventory, rawcycpp_shape_startup_inventory + 1);
    int rawcycpp_shape_buy_quantity[1] = {-1};
    cycpp_shape_buy_quantity = std::vector<int>(rawcycpp_shape_buy_quantity, rawcycpp_shape_buy_quantity + 1);
    int rawcycpp_shape_fuel_incommod[1] = {-1};
    cycpp_shape_fuel_incommod = std::vector<int>(rawcycpp_shape_fuel_incommod, rawcycpp_shape_fuel_incommod + 1);
    int rawcycpp_shape_blanket_size[1] = {-1};
    cycpp_shape_blanket_size = std::vector<int>(rawcycpp_shape_blanket_size, rawcycpp_shape_blanket_size + 1);
    int rawcycpp_shape_blanket_incommod[1] = {-1};
    cycpp_shape_blanket_incommod = std::vector<int>(rawcycpp_shape_blanket_incommod, rawcycpp_shape_blanket_incommod + 1);
    int rawcycpp_shape_blanket_inrecipe[1] = {-1};
    cycpp_shape_blanket_inrecipe = std::vector<int>(rawcycpp_shape_blanket_inrecipe, rawcycpp_shape_blanket_inrecipe + 1);
    int rawcycpp_shape_tritium_core[2] = {-1, -1};
    cycpp_shape_tritium_core = std::vector<int>(rawcycpp_shape_tritium_core, rawcycpp_shape_tritium_core + 2);
    int rawcycpp_shape_tritium_storage[2] = {-1, -1};
    cycpp_shape_tritium_storage = std::vector<int>(rawcycpp_shape_tritium_storage, rawcycpp_shape_tritium_storage + 2);
    int rawcycpp_shape_helium_storage[2] = {-1, -1};
    cycpp_shape_helium_storage = std::vector<int>(rawcycpp_shape_helium_storage, rawcycpp_shape_helium_storage + 2);
    int rawcycpp_shape_blanket[2] = {-1, -1};
    cycpp_shape_blanket = std::vector<int>(rawcycpp_shape_blanket, rawcycpp_shape_blanket + 2);
    cyclus::QueryResult qr = b->Query("Info", NULL);
    fusion_power = qr.GetVal<double>("fusion_power");
    TBR = qr.GetVal<double>("TBR");
    reserve_inventory = qr.GetVal<double>("reserve_inventory");
    startup_inventory = qr.GetVal<double>("startup_inventory");
    buy_quantity = qr.GetVal<double>("buy_quantity");
    fuel_incommod = qr.GetVal<std::string>("fuel_incommod");
    blanket_size = qr.GetVal<double>("blanket_size");
    blanket_incommod = qr.GetVal<std::string>("blanket_incommod");
    blanket_inrecipe = qr.GetVal<std::string>("blanket_inrecipe");
    tritium_core.capacity(1000);
    tritium_storage.capacity(1000);
    helium_storage.capacity(1000);
    blanket.capacity(1000);
  };

  virtual void InfileToDb(cyclus::InfileTree* tree, cyclus::DbInit di) {
    cyclus::Facility::InfileToDb(tree, di);
    int rawcycpp_shape_fusion_power[1] = {-1};
    cycpp_shape_fusion_power = std::vector<int>(rawcycpp_shape_fusion_power, rawcycpp_shape_fusion_power + 1);
    int rawcycpp_shape_TBR[1] = {-1};
    cycpp_shape_TBR = std::vector<int>(rawcycpp_shape_TBR, rawcycpp_shape_TBR + 1);
    int rawcycpp_shape_reserve_inventory[1] = {-1};
    cycpp_shape_reserve_inventory = std::vector<int>(rawcycpp_shape_reserve_inventory, rawcycpp_shape_reserve_inventory + 1);
    int rawcycpp_shape_startup_inventory[1] = {-1};
    cycpp_shape_startup_inventory = std::vector<int>(rawcycpp_shape_startup_inventory, rawcycpp_shape_startup_inventory + 1);
    int rawcycpp_shape_buy_quantity[1] = {-1};
    cycpp_shape_buy_quantity = std::vector<int>(rawcycpp_shape_buy_quantity, rawcycpp_shape_buy_quantity + 1);
    int rawcycpp_shape_fuel_incommod[1] = {-1};
    cycpp_shape_fuel_incommod = std::vector<int>(rawcycpp_shape_fuel_incommod, rawcycpp_shape_fuel_incommod + 1);
    int rawcycpp_shape_blanket_size[1] = {-1};
    cycpp_shape_blanket_size = std::vector<int>(rawcycpp_shape_blanket_size, rawcycpp_shape_blanket_size + 1);
    int rawcycpp_shape_blanket_incommod[1] = {-1};
    cycpp_shape_blanket_incommod = std::vector<int>(rawcycpp_shape_blanket_incommod, rawcycpp_shape_blanket_incommod + 1);
    int rawcycpp_shape_blanket_inrecipe[1] = {-1};
    cycpp_shape_blanket_inrecipe = std::vector<int>(rawcycpp_shape_blanket_inrecipe, rawcycpp_shape_blanket_inrecipe + 1);
    int rawcycpp_shape_tritium_core[2] = {-1, -1};
    cycpp_shape_tritium_core = std::vector<int>(rawcycpp_shape_tritium_core, rawcycpp_shape_tritium_core + 2);
    int rawcycpp_shape_tritium_storage[2] = {-1, -1};
    cycpp_shape_tritium_storage = std::vector<int>(rawcycpp_shape_tritium_storage, rawcycpp_shape_tritium_storage + 2);
    int rawcycpp_shape_helium_storage[2] = {-1, -1};
    cycpp_shape_helium_storage = std::vector<int>(rawcycpp_shape_helium_storage, rawcycpp_shape_helium_storage + 2);
    int rawcycpp_shape_blanket[2] = {-1, -1};
    cycpp_shape_blanket = std::vector<int>(rawcycpp_shape_blanket, rawcycpp_shape_blanket + 2);
    cyclus::InfileTree* sub = tree->SubTree("config/*");
    int i;
    int n;
    {
      double fusion_power_val = cyclus::Query<double>(sub, "fusion_power");
      fusion_power = fusion_power_val;
    }
    {
      double TBR_val = cyclus::Query<double>(sub, "TBR");
      TBR = TBR_val;
    }
    {
      double reserve_inventory_val = cyclus::Query<double>(sub, "reserve_inventory");
      reserve_inventory = reserve_inventory_val;
    }
    {
      double startup_inventory_val = cyclus::Query<double>(sub, "startup_inventory");
      startup_inventory = startup_inventory_val;
    }
    {
      double buy_quantity_val = cyclus::Query<double>(sub, "buy_quantity");
      buy_quantity = buy_quantity_val;
    }
    {
      std::string fuel_incommod_val = cyclus::Query<std::string>(sub, "fuel_incommod");
      fuel_incommod = fuel_incommod_val;
    }
    if (sub->NMatches("blanket_size") > 0) {
      {
        double blanket_size_val = cyclus::Query<double>(sub, "blanket_size");
        blanket_size = blanket_size_val;
      }
    } else {
      double blanket_size_tmp = 100.0;
      blanket_size = blanket_size_tmp;
    }
    {
      std::string blanket_incommod_val = cyclus::Query<std::string>(sub, "blanket_incommod");
      blanket_incommod = blanket_incommod_val;
    }
    {
      std::string blanket_inrecipe_val = cyclus::Query<std::string>(sub, "blanket_inrecipe");
      blanket_inrecipe = blanket_inrecipe_val;
    }
    di.NewDatum("Info")
    ->AddVal("fusion_power", fusion_power, &cycpp_shape_fusion_power)
    ->AddVal("TBR", TBR, &cycpp_shape_TBR)
    ->AddVal("reserve_inventory", reserve_inventory, &cycpp_shape_reserve_inventory)
    ->AddVal("startup_inventory", startup_inventory, &cycpp_shape_startup_inventory)
    ->AddVal("buy_quantity", buy_quantity, &cycpp_shape_buy_quantity)
    ->AddVal("fuel_incommod", fuel_incommod, &cycpp_shape_fuel_incommod)
    ->AddVal("blanket_size", blanket_size, &cycpp_shape_blanket_size)
    ->AddVal("blanket_incommod", blanket_incommod, &cycpp_shape_blanket_incommod)
    ->AddVal("blanket_inrecipe", blanket_inrecipe, &cycpp_shape_blanket_inrecipe)
    ->Record();
  };

  virtual cyclus::Agent* Clone() {
    fusion::Reactor* m = new fusion::Reactor(context());
    m->InitFrom(this);
    return m;
  };

  virtual std::string schema() {
    return ""
      "<interleave>\n"
      "    <element name=\"fusion_power\">\n"
      "        <data type=\"double\"/>\n"
      "    </element>\n"
      "    <element name=\"TBR\">\n"
      "        <data type=\"double\"/>\n"
      "    </element>\n"
      "    <element name=\"reserve_inventory\">\n"
      "        <data type=\"double\"/>\n"
      "    </element>\n"
      "    <element name=\"startup_inventory\">\n"
      "        <data type=\"double\"/>\n"
      "    </element>\n"
      "    <element name=\"buy_quantity\">\n"
      "        <data type=\"double\"/>\n"
      "    </element>\n"
      "    <element name=\"fuel_incommod\">\n"
      "        <data type=\"string\"/>\n"
      "    </element>\n"
      "    <optional>\n"
      "        <element name=\"blanket_size\">\n"
      "            <data type=\"double\"/>\n"
      "        </element>\n"
      "    </optional>\n"
      "    <element name=\"blanket_incommod\">\n"
      "        <data type=\"string\"/>\n"
      "    </element>\n"
      "    <element name=\"blanket_inrecipe\">\n"
      "        <data type=\"string\"/>\n"
      "    </element>\n"
      "</interleave>\n";
  };

  virtual Json::Value annotations() {
    Json::Value root;
    Json::Reader reader;
    bool parsed_ok = reader.parse(
      "{\"name\":\"fusion::Reactor\",\"entity\":\"facility\",\"par"
      "ents\":[\"cyclus::Facility\"],\"all_parents\":[\"cyclus:"
      ":Agent\",\"cyclus::Facility\",\"cyclus::Ider\",\"cyclus:"
      ":StateWrangler\",\"cyclus::TimeListener\",\"cyclus::Tr"
      "ader\"],\"vars\":{\"fusion_power\":{\"doc\":\"Nameplate "
      "fusion power of the reactor\",\"tooltip\":\"Nameplate "
      "fusion power\",\"units\":\"MW\",\"uilabel\":\"Fusion Power"
      "\",\"type\":\"double\",\"index\":0,\"shape\":[-"
      "1],\"alias\":\"fusion_power\"},\"TBR\":{\"doc\":\"Achievabl"
      "e system tritium breeding ratio before "
      "decay\",\"tooltip\":\"Achievable system tritium "
      "breeding ratio before decay\",\"units\":\"non-"
      "dimensional\",\"uilabel\":\"Tritium Breeding Ratio\",\"t"
      "ype\":\"double\",\"index\":1,\"shape\":[-"
      "1],\"alias\":\"TBR\"},\"reserve_inventory\":{\"doc\":\"Mini"
      "mum tritium inventory to hold in reserve in case "
      "of tritium recovery system "
      "failure\",\"tooltip\":\"Minimum tritium inventory to "
      "hold in reserve (excluding core "
      "invneotry)\",\"units\":\"kg\",\"uilabel\":\"Reserve Invent"
      "ory\",\"type\":\"double\",\"index\":2,\"shape\":[-"
      "1],\"alias\":\"reserve_inventory\"},\"startup_inventory"
      "\":{\"doc\":\"Tritium core inventory required to start"
      " reactor\",\"tooltip\":\"Tritium core inventory "
      "required to start "
      "reactor\",\"units\":\"kg\",\"uilabel\":\"Start-up Inventor"
      "y\",\"type\":\"double\",\"index\":3,\"shape\":[-"
      "1],\"alias\":\"startup_inventory\"},\"buy_quantity\":{\"d"
      "oc\":\"Quantity of fuel which reactor tries to "
      "purchase\",\"tooltip\":\"Defaults to fill reserve "
      "inventory\",\"units\":\"kg\",\"uilabel\":\"Buy quantity\",\""
      "type\":\"double\",\"index\":4,\"shape\":[-"
      "1],\"alias\":\"buy_quantity\"},\"fuel_incommod\":{\"doc\":"
      "\"Fresh fuel commodity\",\"tooltip\":\"Name of fuel "
      "commodity requested\",\"uilabel\":\"Fuel input commodi"
      "ty\",\"type\":\"std::string\",\"index\":5,\"shape\":[-"
      "1],\"alias\":\"fuel_incommod\"},\"blanket_size\":{\"defau"
      "lt\":100.0,\"doc\":\"Initial mass of full blanket "
      "material\",\"tooltip\":\"Only blanket material mass, "
      "not structural mass\",\"uilabel\":\"Initial Mass of Bl"
      "anket\",\"type\":\"double\",\"index\":6,\"shape\":[-"
      "1],\"alias\":\"blanket_size\"},\"blanket_incommod\":{\"do"
      "c\":\"Fresh fuel commodity\",\"tooltip\":\"Name of fuel "
      "commodity requested\",\"uilabel\":\"Fuel input commodi"
      "ty\",\"type\":\"std::string\",\"index\":7,\"shape\":[-"
      "1],\"alias\":\"blanket_incommod\"},\"blanket_inrecipe\":"
      "{\"doc\":\"Fresh fuel commodity\",\"tooltip\":\"Name of "
      "fuel commodity requested\",\"uilabel\":\"Fuel input co"
      "mmodity\",\"type\":\"std::string\",\"index\":8,\"shape\":[-"
      "1],\"alias\":\"blanket_inrecipe\"},\"tritium_core\":{\"ca"
      "pacity\":\"1000\",\"type\":[\"cyclus::toolkit::ResBuf\",\""
      "cyclus::Material\"],\"index\":9,\"shape\":[-1,-"
      "1]},\"tritium_storage\":{\"capacity\":\"1000\",\"type\":[\""
      "cyclus::toolkit::ResBuf\",\"cyclus::Material\"],\"inde"
      "x\":10,\"shape\":[-1,-"
      "1]},\"helium_storage\":{\"capacity\":\"1000\",\"type\":[\"c"
      "yclus::toolkit::ResBuf\",\"cyclus::Material\"],\"index"
      "\":11,\"shape\":[-1,-"
      "1]},\"blanket\":{\"capacity\":\"1000\",\"type\":[\"cyclus::"
      "toolkit::ResBuf\",\"cyclus::Material\"],\"index\":12,\"s"
      "hape\":[-1,-1]}},\"doc\":\"A stub facility is provided"
      " as a skeleton for the design of new facility "
      "agents.\"}", root);
    if (!parsed_ok) {
      throw cyclus::ValueError("failed to parse annotations for fusion::Reactor.");
    }
    return root;
  };

  virtual void InitInv(cyclus::Inventories& inv) {
    tritium_core.Push(inv["tritium_core"]);
        tritium_storage.Push(inv["tritium_storage"]);
        helium_storage.Push(inv["helium_storage"]);
        blanket.Push(inv["blanket"]);
    
  };

  virtual cyclus::Inventories SnapshotInv() {
    cyclus::Inventories invs;
    invs["tritium_core"] = tritium_core.PopNRes(tritium_core.count());
    tritium_core.Push(invs["tritium_core"]);
    invs["tritium_storage"] = tritium_storage.PopNRes(tritium_storage.count());
    tritium_storage.Push(invs["tritium_storage"]);
    invs["helium_storage"] = helium_storage.PopNRes(helium_storage.count());
    helium_storage.Push(invs["helium_storage"]);
    invs["blanket"] = blanket.PopNRes(blanket.count());
    blanket.Push(invs["blanket"]);
    return invs;
  };

  virtual void Snapshot(cyclus::DbInit di) {
    di.NewDatum("Info")
    ->AddVal("fusion_power", fusion_power, &cycpp_shape_fusion_power)
    ->AddVal("TBR", TBR, &cycpp_shape_TBR)
    ->AddVal("reserve_inventory", reserve_inventory, &cycpp_shape_reserve_inventory)
    ->AddVal("startup_inventory", startup_inventory, &cycpp_shape_startup_inventory)
    ->AddVal("buy_quantity", buy_quantity, &cycpp_shape_buy_quantity)
    ->AddVal("fuel_incommod", fuel_incommod, &cycpp_shape_fuel_incommod)
    ->AddVal("blanket_size", blanket_size, &cycpp_shape_blanket_size)
    ->AddVal("blanket_incommod", blanket_incommod, &cycpp_shape_blanket_incommod)
    ->AddVal("blanket_inrecipe", blanket_inrecipe, &cycpp_shape_blanket_inrecipe)
    ->Record();
  };

  #pragma cyclus note {"doc": "A stub facility is provided as a skeleton "                               "for the design of new facility agents."}
#line 49 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

  /// A verbose printer for the Reactor
  virtual std::string str();

  /// Set up policies and buffers:
  virtual void EnterNotify();

  /// The handleTick function specific to the Reactor.
  /// @param time the time of the tick
  virtual void Tick();

  /// The handleTick function specific to the Reactor.
  /// @param time the time of the tock
  virtual void Tock();


//-----------------------------------------------------------//
//                     State Variables                       //
//-----------------------------------------------------------//

  #pragma cyclus var {     "doc": "Nameplate fusion power of the reactor",     "tooltip": "Nameplate fusion power",     "units": "MW",     "uilabel": "Fusion Power"   }
#line 75 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  double fusion_power;
  std::vector<int> cycpp_shape_fusion_power;
#line 100 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"


  #pragma cyclus var {     "doc": "Achievable system tritium breeding ratio before decay",     "tooltip": "Achievable system tritium breeding ratio before decay",     "units": "non-dimensional",     "uilabel": "Tritium Breeding Ratio"   }
  double TBR;
  std::vector<int> cycpp_shape_TBR;


  #pragma cyclus var {     "doc": "Minimum tritium inventory to hold in reserve in case of tritium recovery system failure",     "tooltip": "Minimum tritium inventory to hold in reserve (excluding core invneotry)",     "units": "kg",     "uilabel": "Reserve Inventory"   }
  double reserve_inventory;
  std::vector<int> cycpp_shape_reserve_inventory;


  #pragma cyclus var {     "doc": "Tritium core inventory required to start reactor",     "tooltip": "Tritium core inventory required to start reactor",     "units": "kg",     "uilabel": "Start-up Inventory"   }
  double startup_inventory;
  std::vector<int> cycpp_shape_startup_inventory;



  #pragma cyclus var {     "doc": "Quantity of fuel which reactor tries to purchase",     "tooltip": "Defaults to fill reserve inventory",     "units": "kg",     "uilabel": "Buy quantity"   }
#line 108 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  double buy_quantity;
  std::vector<int> cycpp_shape_buy_quantity;
#line 109 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"


  #pragma cyclus var {     "doc": "Fresh fuel commodity",     "tooltip": "Name of fuel commodity requested",     "uilabel": "Fuel input commodity"   }
#line 115 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  std::string fuel_incommod;
  std::vector<int> cycpp_shape_fuel_incommod;
#line 117 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
/* !Marked for deletion!
  #pragma cyclus var {     "doc": "Fresh fuel recipe",     "tooltip": "Fresh fuel recipe",     "uilabel": "Fuel Input Recipe"   }
#line 123 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  std::string fuel_inrecipe;
*/
  #pragma cyclus var {     "default": 100.0,     "doc": "Initial mass of full blanket material",     "tooltip": "Only blanket material mass, not structural mass",     "uilabel": "Initial Mass of Blanket"   }
#line 131 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  double blanket_size;
  std::vector<int> cycpp_shape_blanket_size;
#line 132 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"


  #pragma cyclus var {     "doc": "Fresh fuel commodity",     "tooltip": "Name of fuel commodity requested",     "uilabel": "Fuel input commodity"   }
#line 138 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  std::string blanket_incommod;
  std::vector<int> cycpp_shape_blanket_incommod;
#line 139 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"


  #pragma cyclus var {     "doc": "Fresh fuel commodity",     "tooltip": "Name of fuel commodity requested",     "uilabel": "Fuel input commodity"   }
#line 145 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  std::string blanket_inrecipe;
  std::vector<int> cycpp_shape_blanket_inrecipe;
#line 146 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
/*

    #pragma cyclus var {     "doc": "Fresh Fuel recipe",     "tooltip": "Fresh fuel recipe",     "uilabel": "Fuel Input Recipe"   }
#line 153 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
  std::string blanket_inrecipe;
*/

  bool operational = false; 
//-----------------------------------------------------------//
//                     Materail Buffers                      //
//-----------------------------------------------------------//
#line 161 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"
/*These must be defined after member variables for some reason?*/

  //Tritium stored in the core of the reactor
  #pragma cyclus var {"capacity" : "1000"} //capacity set to 1000 arbitrarily
  cyclus::toolkit::ResBuf<cyclus::Material> tritium_core;
  std::vector<int> cycpp_shape_tritium_core;

#line 166 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

  //Tritium stored in the reserve system of the reactor
  #pragma cyclus var {"capacity" : "1000"}
  cyclus::toolkit::ResBuf<cyclus::Material> tritium_storage;
  std::vector<int> cycpp_shape_tritium_storage;

#line 170 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

  //helium-3 extracted from decayed tritium and stored by the reactor
  #pragma cyclus var {"capacity" : "1000"}
  cyclus::toolkit::ResBuf<cyclus::Material> helium_storage;
  std::vector<int> cycpp_shape_helium_storage;

#line 174 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

  //blanket material
  #pragma cyclus var {"capacity" : "1000"}
  cyclus::toolkit::ResBuf<cyclus::Material> blanket;
  std::vector<int> cycpp_shape_blanket;

#line 178 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.h"

//-----------------------------------------------------------//
//                   Buy and Sell Policies                   //
//-----------------------------------------------------------//
  cyclus::toolkit::MatlBuyPolicy fuel_startup_policy;
  cyclus::toolkit::MatlBuyPolicy fuel_schedule_policy;
  cyclus::toolkit::MatlBuyPolicy fuel_refill_policy;
  cyclus::toolkit::MatlBuyPolicy blanket_startup_policy;


  cyclus::toolkit::MatlSellPolicy sell_policy;

//-----------------------------------------------------------//
//                     Fusion Functions                      //
//-----------------------------------------------------------//

  void Startup();
  void OperateReactor(double TBR, double burn_rate=55.8);
  void DecayInventory(cyclus::toolkit::ResBuf<cyclus::Material> &inventory);
  void CombineInventory(cyclus::toolkit::ResBuf<cyclus::Material> &inventory);
  void ExtractHelium(cyclus::Material::Ptr material);
  void Record(std::string Status, double power);
  void DepleteBlanket(double bred_tritium_mass);
  cyclus::Material::Ptr BreedTritium(double fuel_usage, double TBR);



//-----------------------------------------------------------//
//                      Test Functions                       //
//-----------------------------------------------------------//
  void PrintComp(cyclus::Material::Ptr mat);

  // And away we go!
};

}  // namespace fusion

#endif  // CYCLUS_FUSION_REACTOR_H_