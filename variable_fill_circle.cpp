//
// Created by Luke on 4/21/2020.
//

#include "variable_fill_circle.h"
#include "main.h"

Variable_Fill_Circle::Variable_Fill_Circle() : Circle() {}

Variable_Fill_Circle::Variable_Fill_Circle(point2D center, double radius,  double fill_percent, color fill,
        color border_fill, color background_fill, color overflow_fill) : Circle(fill, center, radius) {
    this->background_fill = background_fill;
    this->border_fill = border_fill;
    this->fill_percent = fill_percent;
    this->overflow_fill = overflow_fill;
}

void Variable_Fill_Circle::draw() const {
    if (fill_percent <= 1) {
        draw_border();
        draw_inner();
    } else {
        draw_inner();
        draw_border();
    }
}

void Variable_Fill_Circle::draw_outer() const {
    // DRAW OUTER CIRCLE
    // Set drawing color to border fill color
    glColor3f(border_fill.red, border_fill.green, border_fill.blue);
    // Draw circle as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of circle
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + ((radius+1.5) * cos(i)),
                   center.y + ((radius+1.5) * sin(i)));
    }
    // End Triangle Fan
    glEnd();
}

void Variable_Fill_Circle::draw_background() const {
    // DRAW BACKGROUND CIRCLE
    // background becomes inner if fill > 100%
    // Set drawing color
    if (fill_percent > 1) {
        // Set drawing color to inner fill color if there's overflow
        glColor3f(fill.red, fill.green, fill.blue);
    } else {
        // background color if no overflow
        glColor3f(background_fill.red, background_fill.green, background_fill.blue);
    }
    // Draw circle as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of circle
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + (radius * cos(i)),
                   center.y + (radius * sin(i)));
    }
    // End Triangle Fan
    glEnd();
}

void Variable_Fill_Circle::draw_border() const {
    draw_outer();
    draw_background();
}

void Variable_Fill_Circle::draw_inner() const {
    // DRAW INNER CIRCLE
    // inner becomes overflow if fill > 100%
    // Set drawing color
    if (fill_percent > 1) {
        // Set drawing color to overflow fill color if there's overflow
        glColor3f(overflow_fill.red, overflow_fill.green, overflow_fill.blue);
    } else {
        // fill color if no overflow
        glColor3f(fill.red, fill.green, fill.blue);
    }
    // Draw circle as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of circle
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + ((radius*fill_percent) * cos(i)),
                   center.y + ((radius*fill_percent) * sin(i)));
    }
    // End Triangle Fan
    glEnd();
}

double Variable_Fill_Circle::get_fill_percent() const {
    return fill_percent;
}

void Variable_Fill_Circle::set_fill_percent(double fill_percent) {
    this->fill_percent = fill_percent;
}

const color &Variable_Fill_Circle::get_background_fill() const {
    return background_fill;
}

void Variable_Fill_Circle::set_background_fill(const color &background_fill) {
    this->background_fill = background_fill;
}

void Variable_Fill_Circle::set_border_fill(const color &border_fill) {
    Variable_Fill_Circle::border_fill = border_fill;
}

const color &Variable_Fill_Circle::get_border_fill() const {
    return border_fill;
}

const color &Variable_Fill_Circle::get_overflow_fill() const {
    return overflow_fill;
}

void Variable_Fill_Circle::set_overflow_fill(const color &overflow_fill) {
    Variable_Fill_Circle::overflow_fill = overflow_fill;
}
