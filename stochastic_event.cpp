//
// Created by Luke on 4/30/2020.
//

#include "stochastic_event.h"

stochastic_event::stochastic_event() {
    this->probability = 0;
}

stochastic_event::stochastic_event(double probability) {
    this->probability = probability;
}

double stochastic_event::get_probability() const {
    return probability;
}
