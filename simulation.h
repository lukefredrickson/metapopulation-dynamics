//
// Created by Luke on 4/22/2020.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include <algorithm>
#include "patch.h"
#include <vector>
#include <memory>
#include "Eigen/Dense"
#include <iostream>
#include <utility>
#include "main.h"

// forward declaration to enable use in vector
class Stochastic_Event;

enum season{SUMMER, FALL, WINTER, SPRING};

using namespace std;
class Simulation {
private:
    Species species;
    // vector of all ecosystem patches
    vector<unique_ptr<Patch>> ecosystem;
    int generations_to_run;
    int current_generation;
    // unit interval determining winter carrying capacity as a proportion of summer carrying capacity
    double winter_harshness;
    bool running;
    season current_season;
    // matrix of distances from each patch to every other patch
    Eigen::MatrixXd distances;
    // vector of populations
    Eigen::VectorXd populations;
    // first order markov chain used to calculate migration
    Eigen::MatrixXd migration_markov;
    // vector of possible stochastic events
    vector<unique_ptr<Stochastic_Event>> stochastic_events;

    /*
     * Requires: nothing
     * Modifies: populations
     * Effects: initializes population vector
     */
    void fill_populations();

    /*
     * Requires: nothing
     * Modifies: distances
     * Effects: initializes distances vector and fills distances between patches
     */
    void fill_distances();

    /*
     * Requires: nothing
     * Modifies: migration_markov
     * Effects: initializes migration markov matrix based on distances between patches and species characteristics
     */
    void fill_migration_markov();

    /*
     * Requires: nothing
     * Modifies: populations
     * Effects: loops through patches in ecosystem, grabbing population data and updating population vector
     */
    void update_populations_vector_from_patches();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: updates patch population data from populations vector
     */
    void update_patch_populations_from_vector();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: simulate summer season, increment generation
     */
    void summer();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: simulate fall season, migrate
     */
    void fall();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: simulate winter season
     */
    void winter();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: simulate spring season
     */
    void spring();

    /*
     * Requires: nothing
     * Modifies: current_generation
     * Effects: ++current_generation
     */
    void increment_current_generation();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: determines natural extinction and simulates population growth in each patch, coloring appropriately
     *          based on positive or negative population change
     */
    void simulate_population_change();

    /*
     * Requires: filled matrices
     * Modifies: populations
     * Effects: use migration markov and species properties to calculate population migration
     */
    void simulate_migration();

    /**
     * Requires: double > 0
     * Modifies: ecosystem
     * Effect: adjust the carrying capacity (radius) of each patch in the ecosystem by some multiplier
     */
    void adjust_carrying_capacity(double multiplier);

    /*
     * Requires: nothing
     * Modifies: populations, distances, migration_markov
     * Effects: initialize all matrices
     */
    void initialize_matrices();

    /*
     * Requires: nothing
     * Modifies: simulation
     * Effects: simulate stochastic events
     */
    void simulate_stochastic_events();

public:
    // CONSTRUCTORS //
    Simulation();
    Simulation(int generations_to_run, Species species, double winter_harshness);

    // GETTERS & SETTERS //
    const Species &get_species() const;
    void set_species(const Species &species);
    vector<unique_ptr<Patch>> &get_ecosystem();
    int get_generations_to_run() const;
    void set_generations_to_run(int generations_to_run);
    int get_current_generation() const;
    bool is_running() const;

    /*
     * Requires: valid Variable_Fill_Circle
     * Modifies: ecosystem
     * Effects: adds a patch to the ecosystem
     */
    bool add_patch(Variable_Fill_Circle circle);

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: deletes last patch added to ecosystem
     */
    bool delete_last_patch();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: updates the radius of the last patch added
     */
    bool update_radius_last_patch(double radius);

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: updates the population of the last patch added
     */
    bool increment_population_last_patch();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: updates the population of the last patch added
     */
    bool decrement_population_last_patch();

    /*
     * Requires: nothing
     * Modifies: running
     * Effects: sets running to true, initializes matrices
     */
    bool run();

    /*
     * Requires: nothing
     * Modifies: running
     * Effects: sets running to false
     */
    bool stop();

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: draws each patch in ecosystem
     */
    void draw() const;

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: delete patch at index i in ecosystem, reinitialize matrices
     */
    void destroy_patch(int i);

    /*
     * Requires: valid color
     * Modifies: ecosystem
     * Effects: set all patch inner fill colors to color
     */
    void set_patch_colors(color color);

    /*
     * Requires: nothing
     * Modifies: ecosystem
     * Effects: calls appropriate season function
     */
    void simulate_season();

    /*
     * Requires: nothing
     * Modifies: ecosystem, current_season
     * Effects: adjust carrying capacity appropriately for next season, change current_season to next season
     */
    void increment_season();
};


#endif //LF_FINAL_PROJECT_GRAPHICS_SIMULATION_H
