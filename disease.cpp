//
// Created by Luke on 4/30/2020.
//

#include "disease.h"
#include "simulation.h"

Disease::Disease() : Stochastic_Event() {}

Disease::~Disease() = default;

Disease::Disease(double probability, double extinction_probability) :
        Stochastic_Event(probability) {
    this->extinction_probability = extinction_probability;
}

void Disease::execute(Simulation* sim) {
    int extinctions = 0;
    for (unique_ptr<Patch> &p : sim->get_ecosystem()) {
        // each patch has a possibility of infection -> extinction
        // or simply population loss to a random degree
        double rand = utilities::random_unit_interval();
        if (rand < extinction_probability) {
            ++extinctions;
            p->go_extinct();
        } else {
            p->update_population(p->get_population()*utilities::random_unit_interval());
        }
    }
    cout << "(disease extinctions: " << extinctions << ")\t";
}

double Disease::get_extinction_probability() const {
    return extinction_probability;
}

void Disease::set_extinction_probability(double extinction_probability) {
    this->extinction_probability = extinction_probability;
}
