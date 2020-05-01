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

class Stochastic_Event;

enum season{SUMMER, FALL, WINTER, SPRING};

using namespace std;
class Simulation {
private:
    Species species;
    vector<unique_ptr<Patch>> ecosystem;
    int generations_to_run;
    int current_generation;
    double winter_harshness;
    bool running;
    season current_season;
    Eigen::MatrixXd distances;
    Eigen::VectorXd populations;
    Eigen::MatrixXd migration_markov;
    vector<unique_ptr<Stochastic_Event>> stochastic_events;

    void fill_populations();

    void fill_distances();

    void fill_migration_markov();

    void update_populations_vector_from_patches();

    void update_patch_populations_from_vector();

    void summer();
    void fall();
    void winter();
    void spring();
    void increment_current_generation();

    void simulate_population_change();

    void simulate_migration();

    void adjust_carrying_capacity(double multiplier);

    void initialize_matrices();

    void simulate_stochastic_events();

public:
    Simulation();
    Simulation(int generations_to_run, Species species, double winter_harshness);

    const Species &get_species() const;

    void set_species(const Species &species);

    vector<unique_ptr<Patch>> &get_ecosystem();

    int get_generations_to_run() const;

    void set_generations_to_run(int generations_to_run);

    int get_current_generation() const;

    bool is_running() const;

    bool add_patch(Variable_Fill_Circle circle);

    bool delete_last_patch();

    const unique_ptr<Patch>& get_last_patch();

    bool update_radius_last_patch(double radius);

    bool increment_population_last_patch();

    bool decrement_population_last_patch();

    bool run();

    bool stop();

    void draw() const;

    void destroy_patch(int i);

    void set_patch_colors(color color);

    void simulate_season();
    void increment_season();
};


#endif //LF_FINAL_PROJECT_GRAPHICS_SIMULATION_H
