#include "rectangle.hpp"
#include <iostream>

#include "rectangle.hpp"

Rectangle::Rectangle(Point center, std::string name, int width, int height)
        : Shape(center, std::move(name)), width(width), height(height) {}



void Rectangle::draw(std::ostream& out) const {
    for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < width; ++j) {
            out << '*';
        }
        out << '\n';
    }
}

double Rectangle::area() const {
    return width * height;
}

Shape* Rectangle::clone() const {
    return new Rectangle(*this);
}
