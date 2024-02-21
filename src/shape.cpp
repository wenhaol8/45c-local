#include "shape.hpp"
#include <iostream>

// Constructor for the Shape class
Shape::Shape(Point center, std::string name) : center(center), name(std::move(name)) {}

// Print function for the Shape class
void Shape::print(std::ostream& out) const {
    double areaValue = this->area();
    out << name << " at (" << center.x << ", " << center.y << ") area = " << areaValue << '\n';
}