//
// Created by Luke on 4/21/2020.
//

#include "patch.h"
#include <utility>


Patch::Patch() : Variable_Fill_Circle() {
    this -> pop_percent_increment = 0.05;
}

Patch::Patch(Variable_Fill_Circle circle, Species species) : Patch(species, circle.getColor(), circle.getCenter(), circle.getRadius(),
        circle.get_background_fill(), circle.get_fill_percent()) {}

Patch::Patch(Species species, color fill, point2D center, double radius, color background_fill, double fill_percent) :
        Variable_Fill_Circle(fill, center, radius, background_fill, fill_percent)  {
    this -> pop_percent_increment = 0.05;
    this -> species = species;
    this -> max_population = this->getArea();
    this -> population = max_population*this->get_fill_percent();
}

Patch::~Patch() {

}

const Species &Patch::get_species() const {
    return species;
}

int Patch::get_population() const {
    return population;
}

int Patch::get_max_population() const {
    return max_population;
}

double Patch::get_population_percent() const {
    return static_cast<double>(population) / max_population;
}

void Patch::set_population_percent(double pop_percent) {
    pop_percent = pop_percent > 1 ? 1 : (pop_percent < 0 ? 0 : pop_percent);
    population = max_population * pop_percent;
    set_fill_percent(pop_percent);
}

void Patch::increment_pop_percent() {
    set_population_percent(get_population_percent()+pop_percent_increment);
}

void Patch::decrement_pop_percent() {
    set_population_percent(get_population_percent()-pop_percent_increment);
}

void Patch::update_radius(double radius) {
    setRadius(radius);
    max_population = getArea();
}