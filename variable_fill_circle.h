//
// Created by Luke on 4/21/2020.
//

#ifndef VARIABLE_FILL_CIRCLE_H
#define VARIABLE_FILL_CIRCLE_H

#include "circle.h"

class Variable_Fill_Circle : public Circle {
protected:
    double fill_percent;
    color background_fill;
    color border_fill;
    color overflow_fill;
private:
    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws inner circle
     */
    void draw_inner() const;
    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws background circle
     */
    void draw_background() const;
    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws outer circle
     */
    void draw_outer() const;

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws outer circle then background circle to create border
     */
    void draw_border() const;
public:
    // CONSTRUCTORS //
    Variable_Fill_Circle();
    Variable_Fill_Circle(point2D center, double radius,  double fill_percent, color fill, color border_fill,
            color background_fill, color overflow_fill);

    // GETTERS & SETTERS //
    double get_fill_percent() const;
    void set_fill_percent(double fill_percent);
    const color &get_background_fill() const;
    void set_background_fill(const color &background_fill);
    const color &get_overflow_fill() const;
    void set_overflow_fill(const color &overflow_fill);
    const color &get_border_fill() const;
    void set_border_fill(const color &border_fill);

    /*
     * Requires: nothing
     * Modifies: nothing
     * Effects: draws inner circle and border circle using fill percent to determine draw order
     */
    void draw() const override;
};


#endif //LF_FINAL_PROJECT_GRAPHICS_VARIABLE_FILL_CIRCLE_H
