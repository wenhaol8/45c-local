#include "triangle.hpp"
#include <algorithm>
#include <iostream>

Triangle::Triangle(Point center, double base, double height, std::string name)
        : Shape(center, std::move(name)), base(base), height(height) {}

void Triangle::draw(std::ostream& out) const {
    int offset = std::max(height, base);
    for (int i = 0; i < height; i += 2) {
        for (int j = 0; j < (offset - i) / 2; ++j) {
            out << ' ';
        }
        for (int k = 0; k <= i; ++k) {
            out << '*';
        }
        out << '\n';
    }
}

double Triangle::area() const {
    return 0.5 * base * height;
}

Shape* Triangle::clone() const {
    return new Triangle(*this);
}
