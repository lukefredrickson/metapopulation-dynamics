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

    /*
     * Requires: nothing
     * Modifies: population
     * Effects: sets population using fill percent
     */
    void set_pop_from_fill_percent();

    /*
     * Requires: nothing
     * Modifies: fill_percent
     * Effects: sets fill percent using population
     */
    void set_fill_percent_from_pop();

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects calculates probability of extinction using population and species characteristics
     */
    double extinction_probability();


public:
    // CONSTRUCTORS //
    Patch();
    Patch(Variable_Fill_Circle circle, Species species);
    Patch(Species species, point2D center, double radius,  double fill_percent, color fill, color background_fill,
            color border_fill, color overflow_fill);
    virtual ~Patch();

    // GETTERS & SETTERS //
    const Species &get_species() const;
    double get_population() const;
    double get_max_population() const;

    /*
     * Requires: positive double
     * Modifies: population, fill_percent
     * Effects: updates population and then fill percent from population
     */
    void update_population(double pop);

    /*
     * Requires: nothing
     * Modifies: fill_percent
     * Effects: increments fill percent by 1% and updates population
     */
    void increment_fill_percent();

    /*
     * Requires: nothing
     * Modifies: fill_percent
     * Effects: decrements fill percent by 1% and updates population
     */
    void decrement_fill_percent();

    /*
     * Requires: nothing
     * Modifies: radius, fill_percent, max_population
     * Effects: changes the radius of the patch, which changes fill percentage and carrying capacity
     */
    void update_carrying_capacity(double radius);

    /*
     * Requires: nothing
     * Modifies: population
     * Effects: calculates population change using logistic growth equation and species characteristics
     */
    double simulate_population_growth();

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: compare random unit interval to extinction probability to decide extinction
     */
    bool decide_extinction();

    /*
     * Requires: nothing
     * Modifies: population
     * Effects: updates population to 0
     */
    void go_extinct();
};


#endif //LF_FINAL_PROJECT_GRAPHICS_HABITAT_H
