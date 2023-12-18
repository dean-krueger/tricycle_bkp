
#line 1 "/home/dean/Wisconsin/cyclus_fusion/Fusion/src/reactor.cc"
#include "reactor.h"

namespace fusion {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Reactor::Reactor(cyclus::Context* ctx) : cyclus::Facility(ctx) {}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
std::string Reactor::str() {
  return Facility::str();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Reactor::Tick() {
  std::cout << "Test Tick \n";

}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void Reactor::Tock() {
  std::cout << "Test Tock \n";
}

// WARNING! Do not change the following this function!!! This enables your
// archetype to be dynamically loaded and any alterations will cause your
// archetype to fail.
extern "C" cyclus::Agent* ConstructReactor(cyclus::Context* ctx) {
  return new Reactor(ctx);
}

}  // namespace fusion