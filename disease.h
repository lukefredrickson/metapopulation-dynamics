//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_DISEASE_H
#define LF_FINAL_PROJECT_GRAPHICS_DISEASE_H

#include "stochastic_event.h"

class Disease : public Stochastic_Event {
private:
    // probability of extinction
    double extinction_probability;
public:
    // CONSTRUCTORS //
    Disease();
    ~Disease();
    explicit Disease(double probability, double extinction_probability);

    // GETTERS & SETTERS //
    double get_extinction_probability() const;
    void set_extinction_probability(double extinction_probability);

    /*
     * Requires: Simulation
     * Modifies: sim
     * Effect: every patch has a chance of going extinct (determined by extinction_probability)
     *          and if a patch survives extinction, its population still diminishes by a random percentage
     */
    void execute(Simulation* sim) override;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_DISEASE_H
