//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_PATCH_DESTRUCTION_H
#define LF_FINAL_PROJECT_GRAPHICS_PATCH_DESTRUCTION_H

#include "stochastic_event.h"

class Patch_Destruction : public Stochastic_Event {
public:
    Patch_Destruction();
    ~Patch_Destruction();
    explicit Patch_Destruction(double probability);
    void execute(Simulation* sim) override;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_PATCH_DESTRUCTION_H
