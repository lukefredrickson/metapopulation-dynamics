//
// Created by Luke on 4/21/2020.
//

#ifndef VARIABLE_FILL_CIRCLE_H
#define VARIABLE_FILL_CIRCLE_H

#include "circle.h"

class Variable_Fill_Circle : public Circle {
private:
    double fill_percent;
    color background_fill;
public:
    Variable_Fill_Circle();
    Variable_Fill_Circle(color fill, point2D center, double radius, color background_fill, double fill_percent);

    double get_fill_percent() const;

    void set_fill_percent(double fill_percent);

    const color &get_background_fill() const;

    void set_background_fill(const color &background_fill);

    void draw() const override;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_VARIABLE_FILL_CIRCLE_H
