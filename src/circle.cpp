#include "circle.hpp"
#include <iostream>
#include <numbers>


// Constructor
Circle::Circle(Point center, std::string name, int radius)
        : Shape(center, std::move(name)), radius(radius) {}

// Area calculation for circle
double Circle::area() const {
    return std::numbers::pi * radius * radius;
}

// Draw method for circle - ASCII art
void Circle::draw(std::ostream& out) const {
    int diameter = radius * 2;
    for (int y = 0; y <= diameter; y += 2) {
        for (int x = 0; x <= diameter; ++x) {
            // Using the equation of a circle to determine if the point (x, y) is inside the circle
            int dx = radius - x; // horizontal distance from the center
            int dy = radius - y; // vertical distance from the center
            if (dx*dx + dy*dy <= radius*radius) {
                out << '*';
            } else {
                out << ' ';
            }
        }
        out << '\n';
    }
}

// Clone method for circle
Circle* Circle::clone() const {
    return new Circle(*this);
}
