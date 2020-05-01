//
// Created by Luke on 4/21/2020.
//

#ifndef HABITAT_H
#define HABITAT_H


#include "variable_fill_circle.h"
#include "species.h"
#include "utilities.h"
#include <iostream>

using namespace std;
class Patch : public Variable_Fill_Circle {
private:
    Species species;
    double population;
    double max_population;


    void set_pop_from_fill_percent();
    void set_fill_percent_from_pop();
    double extinction_probability();


public:
    Patch();
    Patch(Variable_Fill_Circle circle, Species species);
    Patch(Species species, point2D center, double radius,  double fill_percent, color fill, color background_fill,
            color border_fill, color overflow_fill);

    virtual ~Patch();

    const Species &get_species() const;

    double get_population() const;

    void update_population(double pop);

    double get_max_population() const;

    void increment_fill_percent();

    void decrement_fill_percent();

    void update_carrying_capacity(double radius);

    double simulate_population_growth();

    bool decide_extinction();

    void go_extinct();
};


#endif //LF_FINAL_PROJECT_GRAPHICS_HABITAT_H
