#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
protected:
    double radius;
public:
    /* Constructors */
    Circle();
    explicit Circle(double radius);
    explicit Circle(color fill);
    explicit Circle(point2D center);
    Circle(color fill, point2D center);
    Circle(double red, double green, double blue, double alpha);
    Circle(double x, double y);
    Circle(double red, double green, double blue, double alpha, double x, double y);
    Circle(color fill, double x, double y);
    Circle(double red, double green, double blue, double alpha, point2D center);
    Circle(color fill, double radius);
    Circle(point2D center, double radius);
    Circle(color fill, point2D center, double radius);
    Circle(double red, double green, double blue, double alpha, double radius);
    Circle(double x, double y, double radius);
    Circle(double red, double green, double blue, double alpha, double x, double y, double radius);
    Circle(color fill, double x, double y, double radius);
    Circle(double red, double green, double blue, double alpha, point2D center, double radius);

    /* Destructor */
    virtual ~Circle() = default;

    /* Getter */
    double getRadius() const;

    /* Setter */
    void setRadius(double r);
    void changeRadius(double delta);

    /* area */
    double getArea();

    /* Draw */
    void draw() const override;

};

#endif //GRAPHICSEXAMPLES_CIRCLE_H
