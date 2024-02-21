#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include <iostream>

class Rectangle : public Shape {
public:
    Rectangle(Point center, std::string name, int width, int height);
    //void print(std::ostream& out) const override;
    double area() const override;
    void draw(std::ostream& out) const override;
    Shape* clone() const override;

private:
    double width;
    double height;
};

#endif // RECTANGLE_HPP