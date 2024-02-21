#include "picture.hpp"
#include <utility>
#include <algorithm>
#include <iostream>

// Constructor
Picture::Picture() : head(nullptr), tail(nullptr) {}

// Copy constructor
Picture::Picture(const Picture& other) : head(nullptr), tail(nullptr) {
    for (ListNode* node = other.head; node != nullptr; node = node->next) {
        add(*(node->shape));
    }
}

// Move constructor
Picture::Picture(Picture&& other) : head(other.head), tail(other.tail) {
    other.head = nullptr;
    other.tail = nullptr;
}

// Destructor
Picture::~Picture() {
    while (head) {
        ListNode* current = head;
        head = head->next;
        delete current->shape;
        delete current;
    }
}

// Swap function
void Picture::swap(Picture& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

// Copy assignment operator
Picture& Picture::operator=(const Picture& other) {
    Picture temp(other);
    swap(temp);
    return *this;
}

// Move assignment operator
Picture& Picture::operator=(Picture&& other) {
    if (this != &other) {
        Picture temp(std::move(other));
        swap(temp);
    }
    return *this;
}

// Add shape to the picture
void Picture::add(const Shape& shape) {
    ListNode* node = new ListNode{shape.clone(), nullptr};
    if (tail) {
        tail->next = node;
        tail = node;
    } else {
        head = tail = node;
    }
}

// Print all shapes
void Picture::print_all(std::ostream& out) const {
    for (ListNode* node = head; node != nullptr; node = node->next) {
        node->shape->print(out);
    }
}

// Draw all shapes
void Picture::draw_all(std::ostream& out) const {
    for (ListNode* node = head; node != nullptr; node = node->next) {
        node->shape->print(out);
        node->shape->draw(out);
        //out << '\n';
    }
}

// Calculate total area of all shapes
double Picture::total_area() const {
    double total = 0;
    for (ListNode* node = head; node != nullptr; node = node->next) {
        total += node->shape->area();
    }
    return total;
}
