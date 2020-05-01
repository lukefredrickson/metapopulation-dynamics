//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_DISEASE_H
#define LF_FINAL_PROJECT_GRAPHICS_DISEASE_H

#include "stochastic_event.h"

class Disease : public Stochastic_Event {
private:
    double extinction_probability;
public:
    Disease();
    ~Disease();
    explicit Disease(double probability, double extinction_probability);
    void execute(Simulation* sim) override;
    double get_extinction_probability() const;
    void set_extinction_probability(double extinction_probability);
};


#endif //LF_FINAL_PROJECT_GRAPHICS_DISEASE_H
