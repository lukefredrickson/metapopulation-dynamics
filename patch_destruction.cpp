//
// Created by Luke on 4/30/2020.
//

#include "patch_destruction.h"
#include "simulation.h"

Patch_Destruction::Patch_Destruction() : Stochastic_Event() {
}

Patch_Destruction::~Patch_Destruction() = default;

Patch_Destruction::Patch_Destruction(double probability) : Stochastic_Event(probability) {
}

void Patch_Destruction::execute(Simulation* sim) {
    int i = utilities::random_int(0, sim->get_ecosystem().size());
    sim->destroy_patch(i);
    cout << "(patch destruction)\t";
}
