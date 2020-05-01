//
// Created by Luke on 4/22/2020.
//

#ifndef SPECIES_H
#define SPECIES_H


class Species {
private:
    // LOCAL GROWTH PARAMS
    // birth rate - death rate for a species
    double intrinsic_rate_of_increase;
    // MIGRATION PARAMS
    // base proportion of population that will migrate from patch assuming full crowding
    double emigration_proportion;
    // exponent to raise distances to when determining migration probability from one patch to another
    // when this is 1, probability of migration increases linearly with distance
    // a value of 0 means all patches are equally likely, distance won't matter at all
    // a value -1 means probability is inversely linearly correlated with distance
    // a value > 1 will weight probability towards close patches, and a value of < -1 will weight towards far patches
    double migration_distance_weight;
    // proportion of migrants who die in transit
    double migrant_mortality_rate;
    // EXTINCTION PARAMS
    // population at which there is a 50% chance of the local population of a patch going extinct
    double probable_extinction_population;
public:
    // CONSTRUCTORS //
    Species();
    Species(double intrinsic_rate_of_increase,
            double emigration_proportion, double migration_distance, double migrant_mortality_rate,
            double probable_extinction_population);
    ~Species();

    // GETTERS & SETTERS //
    double get_population_increase_rate() const;
    void set_population_increase_rate(double population_increase_rate);
    double get_emigration_proportion() const;
    void set_emigration_proportion(double emigration_proportion);
    double get_migration_distance_weight() const;
    void set_migration_distance_weight(double migration_distance);
    double get_migrant_mortality_rate() const;
    void set_migrant_mortality_rate(double migrant_mortality_rate);
    double get_probable_extinction_population() const;
    void set_probable_extinction_population(double probable_extinction_population);
};


#endif //LF_FINAL_PROJECT_GRAPHICS_SPECIES_H
