//
// Created by Luke on 4/30/2020.
//

#include "utilities.h"

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

double utilities::random_unit_interval() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

int utilities::random_int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}