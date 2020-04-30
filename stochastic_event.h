//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H
#define LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H

#include "simulation.h"

class stochastic_event {
private:
    double probability;
public:
    stochastic_event();
    stochastic_event(double probability);
    double get_probability() const;
    virtual void execute(Simulation sim) = 0;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H
