//
// Created by Luke on 4/21/2020.
//

#ifndef HABITAT_H
#define HABITAT_H


#include "variable_fill_circle.h"
#include "species.h"

class Patch : public Variable_Fill_Circle {
private:
    Species species;
    int population;
    int max_population;
    double pop_percent_increment;
public:
    Patch();
    Patch(Variable_Fill_Circle circle, Species species);
    Patch(Species species, color fill, point2D center, double radius, color background_fill, double fill_percent);

    virtual ~Patch();

    const Species &get_species() const;

    int get_population() const;

    int get_max_population() const;

    double get_population_percent() const;

    void set_population_percent(double pop_percent);

    void increment_pop_percent();

    void decrement_pop_percent();

    void update_radius(double radius);
};


#endif //LF_FINAL_PROJECT_GRAPHICS_HABITAT_H
