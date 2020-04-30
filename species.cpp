//
// Created by Luke on 4/22/2020.
//

#include "species.h"

Species::Species() {}

Species::Species(double intrinsic_rate_of_increase,
                 double emigration_proportion, double migration_distance, double migrant_mortality_rate,
                 double colonization_probability, double probable_extinction_population)
                    : intrinsic_rate_of_increase(intrinsic_rate_of_increase),
                        emigration_proportion(emigration_proportion),
                        migration_distance_weight(migration_distance),
                        migrant_mortality_rate(migrant_mortality_rate),
                        colonization_probability(colonization_probability),
                        probable_extinction_population(
                        probable_extinction_population) {}

Species::~Species() {}

double Species::get_population_increase_rate() const {
    return intrinsic_rate_of_increase;
}

void Species::set_population_increase_rate(double population_increase_rate) {
    this -> intrinsic_rate_of_increase = population_increase_rate;
}

double Species::get_emigration_proportion() const {
    return emigration_proportion;
}

void Species::set_emigration_proportion(double emigration_proportion) {
    this -> emigration_proportion = emigration_proportion;
}

double Species::get_migration_distance_weight() const {
    return migration_distance_weight;
}

void Species::set_migration_distance_weight(double migration_distance) {
    this -> migration_distance_weight = migration_distance;
}

double Species::get_migrant_mortality_rate() const {
    return migrant_mortality_rate;
}

void Species::set_migrant_mortality_rate(double migrant_mortality_rate) {
    this -> migrant_mortality_rate = migrant_mortality_rate;
}

double Species::get_colonization_probability() const {
    return colonization_probability;
}

void Species::set_colonization_probability(double colonization_probability) {
    this -> colonization_probability = colonization_probability;
}

double Species::get_probable_extinction_population() const {
    return probable_extinction_population;
}

void Species::set_probable_extinction_population(double probable_extinction_population) {
    this -> probable_extinction_population = probable_extinction_population;
}

