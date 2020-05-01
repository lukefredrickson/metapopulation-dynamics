//
// Created by Luke on 4/22/2020.
//

#include "simulation.h"
#include "disease.h"
#include "patch_destruction.h"

Simulation::Simulation() {
    species = Species();
    ecosystem = vector<unique_ptr<Patch>>();
    generations_to_run = 0;
    current_generation = 0;
    winter_harshness = 1;
    running = false;
    current_season = SUMMER;
    stochastic_events.push_back(make_unique<Disease>(Disease(0.05, 0.5)));
    stochastic_events.push_back(make_unique<Patch_Destruction>(Patch_Destruction(0.01)));
}

Simulation::Simulation(int generations_to_run, Species species, double winter_harshness) : Simulation() {
    this->species = species;
    this->generations_to_run = generations_to_run;
    this->winter_harshness = winter_harshness;
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
        ecosystem.back()->update_carrying_capacity(radius);
        return true;
    }
    return false;
}


bool Simulation::increment_population_last_patch() {
    if(!ecosystem.empty()) {
        ecosystem.back()->increment_fill_percent();
        return true;
    }
    return false;
}

bool Simulation::decrement_population_last_patch() {
    if(!ecosystem.empty()) {
        ecosystem.back()->decrement_fill_percent();
        return true;
    }
    return false;
}

bool Simulation::run() {
    running = true;
    initialize_matrices();
    return running;
}

void Simulation::initialize_matrices() {
    fill_populations();
    fill_distances();
    fill_migration_markov();
}

bool Simulation::stop() {
    running = false;
    return running;
}

void Simulation::draw() const {
    for(const unique_ptr<Patch> &p : ecosystem) {
        p->draw();
    }
}

void Simulation::fill_populations() {
    populations = Eigen::VectorXd(ecosystem.size());
    update_populations_vector_from_patches();
}

void Simulation::fill_distances() {
    distances = Eigen::MatrixXd(ecosystem.size(), ecosystem.size());
    for (int row = 0; row < distances.rows(); ++row) {
        for (int col = row + 1; col < distances.cols(); ++col) {
            distances(row, col) = ecosystem[row]->getCenter().distance(ecosystem[col]->getCenter());
            distances(col, row) = distances(row, col);
        }
    }
}

void Simulation::fill_migration_markov() {
    // raise all distance coefficients to -1 power
    migration_markov = distances.array().pow(-species.get_migration_distance_weight());
    // set diagonal to 0
    migration_markov.diagonal().setZero();
    // get sums of cols
    auto sums = migration_markov.colwise().sum();
    // divide each coefficient by the sum of its column. this scales values in each col to sum to 1.
    // the resulting matrix is stochastic, and represents the probability that a migrating individual will go from
    // patch_i to patch_j, where i and j are col_i and row_j of this matrix.
    for (int col = 0; col < migration_markov.cols(); ++col){
        migration_markov.col(col) = migration_markov.col(col).array() / sums(col);
    }
}

void Simulation::update_populations_vector_from_patches() {
    for (int row = 0; row < populations.rows(); ++row) {
        populations(row) = ecosystem[row]->get_population();
    }
}

void Simulation::update_patch_populations_from_vector() {
    for (int row = 0; row < populations.rows(); ++row) {
        ecosystem[row]->update_population(populations(row));
    }
}

void Simulation::simulate_population_change() {
    int nat_extinctions = 0;
    for (unique_ptr<Patch> &p : ecosystem) {
        // decide natural extinction for each patch
        if (p -> get_population() > 0 && p -> decide_extinction()) {
            ++nat_extinctions;
            p -> go_extinct();
        }
        // sim growth for each patch
        double growth = p -> simulate_population_growth();
        // color patch appropriately based on positive/negative/no growth
        if (growth > 0) {
            p -> setColor(color(0, 1, 0));
        } else if (growth < 0) {
            p -> setColor(color(1, 0, 0));
        } else {
            p -> setColor(color(1, 1, 1));
        }
    }
    if (nat_extinctions > 0) {
        cout << "(natural extinctions: " << nat_extinctions << ")\t";
    }
    update_populations_vector_from_patches();
}

void Simulation::simulate_migration() {
    if (ecosystem.size() > 1) {
        set_patch_colors(color(0,0,1));
        // get proportion from each patch that will migrate
        Eigen::VectorXd migrant_population = populations.array() * species.get_emigration_proportion();
        // crowding effect: more migration out of crowded patches
        for (int row = 0; row < migrant_population.rows(); ++row) {
            migrant_population(row) *= ecosystem[row]->get_fill_percent();
        }
        // subtract migrating population from total population
        populations -= migrant_population;
        // kill some proportion of migrants
        migrant_population.array() *= (1-species.get_migrant_mortality_rate());
        // add successful migrants to new patches
        populations += migration_markov*migrant_population;
        update_patch_populations_from_vector();
    }
}

void Simulation::increment_current_generation() {
    current_generation++;
}

void Simulation::set_patch_colors(color color) {
    for (unique_ptr<Patch> &p : ecosystem) {
        p -> setColor(color);
    }
}

void Simulation::adjust_carrying_capacity(double multiplier) {
    for (unique_ptr<Patch> &p : ecosystem) {
        p->update_carrying_capacity(p->getRadius() * multiplier);
    }
}

void Simulation::summer() {
    increment_current_generation();
    simulate_population_change();
}

void Simulation::fall() {
    simulate_migration();
}

void Simulation::winter() {
    simulate_population_change();
}

void Simulation::spring() {
    simulate_population_change();
}

void Simulation::simulate_season() {
    simulate_stochastic_events();
    update_populations_vector_from_patches();
    switch(current_season) {
        case SUMMER: {
            summer();
            cout << "\n\nGeneration " << current_generation;
            cout << "\nSUMMER\t";
            break;
        }
        case FALL: {
            fall();
            cout << "\nFALL\t";
            break;
        }
        case WINTER: {
            winter();
            cout << "\nWINTER\t";
            break;
        }
        case SPRING: {
            spring();
            cout << "\nSPRING\t";
            break;
        }
    }
}

void Simulation::increment_season() {
    set_patch_colors(color(1,1,1));
    switch(current_season) {
        case SUMMER: {
            adjust_carrying_capacity(pow(winter_harshness, 0.5));
            current_season = FALL;
            break;
        }
        case FALL: {
            adjust_carrying_capacity(pow(winter_harshness, 0.5));
            current_season = WINTER;
            break;
        }
        case WINTER: {
            adjust_carrying_capacity(1/pow(winter_harshness, 0.5));
            current_season = SPRING;
            break;
        }
        case SPRING: {
            adjust_carrying_capacity(1/pow(winter_harshness, 0.5));
            current_season = SUMMER;
            break;
        }
    }
}

void Simulation::destroy_patch(int i) {
    ecosystem.erase(ecosystem.begin() + i);
    initialize_matrices();
}

void Simulation::simulate_stochastic_events() {
    // sim stochastic event if it happens
    for (unique_ptr<Stochastic_Event> &e : stochastic_events) {
        if (utilities::random_unit_interval() < e->get_probability()) {
            e->execute(this);
        }
    }
}
