//
// Created by Luke on 4/27/2020.
//

#include "util.h"
#include <random>

double Util::random_unit_interval() {
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}