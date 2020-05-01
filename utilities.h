//
// Created by Luke on 4/30/2020.
//

#ifndef LF_FINAL_PROJECT_GRAPHICS_UTILITIES_H
#define LF_FINAL_PROJECT_GRAPHICS_UTILITIES_H

#endif //LF_FINAL_PROJECT_GRAPHICS_UTILITIES_H

#include <random>

namespace utilities {
    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: creates random double in range [0, 1]
     */
    double random_unit_interval();

    /*
     * Requires: int min and max
     * Modifies: nothing
     * Effects: creates random int in range [min, max], inclusive
     */
    int random_int(int min, int max);
}