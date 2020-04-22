//
// Created by Luke on 4/22/2020.
//

#include "simulation.h"

#include <utility>

Simulation::Simulation() {
    species = Species();
    ecosystem = vector<unique_ptr<Patch>>();
    generations_to_run = 0;
    current_generation = 0;
    running = false;
}

Simulation::Simulation(int generations_to_run, Species species) : Simulation() {
    this->species = species;
    this->generations_to_run = generations_to_run;
}

const Species &Simulation::get_species() const {
    return species;
}

void Simulation::set_species(const Species &species) {
    if (!running) {
        this->species = species;
    }
}

vector<unique_ptr<Patch>> &Simulation::get_ecosystem() {
    return ecosystem;
}

int Simulation::get_generations_to_run() const {
    return generations_to_run;
}

void Simulation::set_generations_to_run(int generations_to_run) {
    if (!running) {
        this->generations_to_run = generations_to_run;
    }
}

int Simulation::get_current_generation() const {
    return current_generation;
}

bool Simulation::is_running() const {
    return running;
}

bool Simulation::add_patch(Variable_Fill_Circle circle) {
    unique_ptr<Patch> p = make_unique<Patch>(circle, species);
    ecosystem.push_back(move(p));
    return true;
}

bool Simulation::delete_last_patch() {
    if(!ecosystem.empty()) {
        ecosystem.pop_back();
        return true;
    }
    return false;
}

bool Simulation::update_radius_last_patch(double radius) {
    if(!ecosystem.empty()) {
        ecosystem.back()->update_radius(radius);
        return true;
    }
    return false;
}


bool Simulation::increment_population_last_patch() {
    if(!ecosystem.empty()) {
        ecosystem.back()->increment_pop_percent();
        return true;
    }
    return false;
}

bool Simulation::decrement_population_last_patch() {
    if(!ecosystem.empty()) {
        ecosystem.back()->decrement_pop_percent();
        return true;
    }
    return false;
}

bool Simulation::run() {
    running = true;
    return running;
}

void Simulation::draw() const {
    for(const unique_ptr<Patch> &p : ecosystem) {
        p->draw();
    }
}

