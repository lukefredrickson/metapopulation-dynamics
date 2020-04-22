//
// Created by Luke on 4/22/2020.
//

#ifndef SIMULATION_H
#define SIMULATION_H

#include "patch.h"
#include <vector>
#include <memory>

using namespace std;
class Simulation {
private:
    Species species;
    vector<unique_ptr<Patch>> ecosystem;
    int generations_to_run;
    int current_generation;
    bool running;
public:
    Simulation();
    Simulation(int generations_to_run, Species species);

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

    void draw() const;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_SIMULATION_H
