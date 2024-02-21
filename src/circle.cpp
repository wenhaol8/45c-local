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
    for(int y = -radius; y <= radius; y += 2){
        for(int x = -radius; x<= radius; ++x){
            out << (x * x + y * y <= radius * radius ? '*' : ' ');
        }
        out << '\n';
    }
}

// Clone method for circle
Circle* Circle::clone() const {
    return new Circle(*this);
}
