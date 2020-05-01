//
// Created by Luke on 4/22/2020.
//

#ifndef SPECIES_H
#define SPECIES_H


class Species {
private:
    // local growth parameters
    double intrinsic_rate_of_increase;
    // migration parameters
    double emigration_proportion;
    double migration_distance_weight;
    double migrant_mortality_rate;
    // extinction
    double probable_extinction_population;
public:
    Species();

    Species(double intrinsic_rate_of_increase,
            double emigration_proportion, double migration_distance, double migrant_mortality_rate,
            double probable_extinction_population);

    ~Species();

    double get_population_increase_rate() const;

    void set_population_increase_rate(double population_increase_rate);

    double get_emigration_proportion() const;

    void set_emigration_proportion(double emigration_proportion);

    double get_migration_distance_weight() const;

    void set_migration_distance_weight(double migration_distance);

    double get_migrant_mortality_rate() const;

    void set_migrant_mortality_rate(double migrant_mortality_rate);

    double get_colonization_probability() const;

    void set_colonization_probability(double colonization_probability);

    double get_probable_extinction_population() const;

    void set_probable_extinction_population(double probable_extinction_population);
};


#endif //LF_FINAL_PROJECT_GRAPHICS_SPECIES_H
