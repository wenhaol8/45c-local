#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "rectangle.hpp"
#include <iostream>

class Square : public Rectangle {
public:
    Square(Point center, double side, std::string name);

    // No need to override area or draw, as they are the same for squares and rectangles
    // Only the constructor is different to ensure width and height are the same
    Shape* clone() const override;
};

#endif // SQUARE_HPP
