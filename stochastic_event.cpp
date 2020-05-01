//
// Created by Luke on 4/30/2020.
//

#include "stochastic_event.h"
#include "simulation.h"

Stochastic_Event::Stochastic_Event() {
    this->probability = 0;
}

Stochastic_Event::~Stochastic_Event()= default;

Stochastic_Event::Stochastic_Event(double probability) {
    this->probability = probability;
}

double Stochastic_Event::get_probability() const {
    return probability;
}
