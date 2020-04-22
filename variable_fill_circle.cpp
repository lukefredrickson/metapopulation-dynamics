//
// Created by Luke on 4/21/2020.
//

#include "variable_fill_circle.h"
#include "main.h"

void Variable_Fill_Circle::draw() const {
    // DRAW OUTER CIRCLE
    // Set drawing color to inner fill color
    glColor3f(fill.red, fill.green, fill.blue);
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

    // DRAW BACKGROUND CIRCLE
    // Set drawing color to inner fill color
    glColor3f(background_fill.red, background_fill.green, background_fill.blue);
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

    // DRAW INNER CIRCLE
    // Set drawing color to inner fill color
    glColor3f(fill.red, fill.green, fill.blue);
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

Variable_Fill_Circle::Variable_Fill_Circle() : Circle() {}

Variable_Fill_Circle::Variable_Fill_Circle(color fill, point2D center, double radius, color background_fill,
                                           double fill_percent) : Circle(fill, center, radius) {
    this->background_fill = background_fill;
    this->fill_percent = fill_percent;
}

double Variable_Fill_Circle::get_fill_percent() const {
    return fill_percent;
}

void Variable_Fill_Circle::set_fill_percent(double fill_percent) {
    this->fill_percent = fill_percent;
    this->draw();
}

const color &Variable_Fill_Circle::get_background_fill() const {
    return background_fill;
}

void Variable_Fill_Circle::set_background_fill(const color &background_fill) {
    this->background_fill = background_fill;
    this->draw();
}