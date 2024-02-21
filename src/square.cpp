#include "square.hpp"

Square::Square(Point center, double side, std::string name)
        : Rectangle(center, side, side, std::move(name)) {}

Shape* Square::clone() const {
    return new Square(*this);
}
