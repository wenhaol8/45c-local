#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"
#include <iostream>

class Triangle : public Shape {
public:
    Triangle(Point center, double base, double height, std::string name);
    //void print(std::ostream& out) const override;
    double area() const override;
    void draw(std::ostream& out) const override;
    Shape* clone() const override;

private:
    double base;
    double height;
};

#endif // TRIANGLE_HPP