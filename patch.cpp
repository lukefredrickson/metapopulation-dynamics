//
// Created by Luke on 4/21/2020.
//

#include "patch.h"

const double FILL_PERCENT_INCREMENT = 0.01;

Patch::Patch() : Variable_Fill_Circle() {
}

Patch::Patch(Variable_Fill_Circle circle, Species species) : Patch(species, circle.getCenter(), circle.getRadius(),
        circle.get_fill_percent(), circle.getColor(), circle.get_background_fill(), circle.get_border_fill(),
        circle.get_overflow_fill()) {}

Patch::Patch(Species species, point2D center, double radius,  double fill_percent, color fill, color background_fill,
        color border_fill, color overflow_fill) :
        Variable_Fill_Circle(center, radius,  fill_percent, fill,background_fill, border_fill, overflow_fill)  {
    this -> species = species;
    this -> max_population = this->getArea();
    set_pop_from_fill_percent();
}

Patch::~Patch() {

}

const Species &Patch::get_species() const {
    return species;
}

double Patch::get_population() const {
    return population;
}

void Patch::update_population(double pop) {
    // make sure population is >0
    pop = pop < 0 ? 0 : pop;
    this -> population = pop;
    // update fill percent
    set_fill_percent_from_pop();
}

double Patch::get_max_population() const {
    return max_population;
}

void Patch::increment_fill_percent() {
    set_fill_percent(this->fill_percent + FILL_PERCENT_INCREMENT);
    set_pop_from_fill_percent();
}

void Patch::decrement_fill_percent() {
    set_fill_percent(this->fill_percent - FILL_PERCENT_INCREMENT);
    set_pop_from_fill_percent();
}

void Patch::update_carrying_capacity(double radius) {
    setRadius(radius);
    set_fill_percent_from_pop();
    max_population = getArea();
}

double Patch::simulate_population_growth() {
    if (decide_extinction()) {
        double pop_before_extinction = population;
        go_extinct();
        return -pop_before_extinction;
    } else {
        double r = species.get_population_increase_rate();
        double population_increase = r*population*(1-(population/max_population));
        update_population(population + population_increase);
        return population_increase;
    }
}

void Patch::go_extinct() {
    update_population(0);
}

/**************** PRIVATE METHODS ****************/

void Patch::set_pop_from_fill_percent() {
    population = PI*pow((this->radius*this->fill_percent), 2);
}

void Patch::set_fill_percent_from_pop() {
    if (population == 0) {
        set_fill_percent(0);
    } else {
        set_fill_percent(pow((population/PI), 0.5) / this->radius);
    }
}

double Patch::extinction_probability() {
    return 1 - (pow(population,2) / (pow(species.get_probable_extinction_population(),2) + pow(population,2)));
}

bool Patch::decide_extinction() {
    return (Util::random_unit_interval() < extinction_probability());
}