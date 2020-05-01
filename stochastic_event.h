//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H
#define LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H

#include "utilities.h"
#include "simulation.h"
#include <memory>

class Simulation;

using namespace std;
class Stochastic_Event {
private:
    double probability;
public:
    Stochastic_Event();
    ~Stochastic_Event();
    explicit Stochastic_Event(double probability);
    double get_probability() const;
    virtual void execute(Simulation* sim) = 0;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_STOCHASTIC_EVENT_H
