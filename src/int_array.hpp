#ifndef INT_ARRAY_HPP
#define INT_ARRAY_HPP

#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>

class Array {
public:

    Array() : len{0}, buf{nullptr} {}


    explicit Array(int len) : len(len), buf(new int[len] {}) {}


    Array(const Array& other) : len(other.len), buf(new int[other.len]) {
        std::copy(other.buf, other.buf + other.len, buf);
    }


    Array(Array&& other) noexcept : len(0), buf(nullptr) {
        swap(*this, other);
    }


    ~Array() {
        delete[] buf;
    }


    Array& operator=(Array other) {
        swap(*this, other);
        return *this;
    }


    int length() const {
        return len;
    }


    int& operator[](int index) {
        if (!in_bounds(index)) throw std::out_of_range("Index out of bounds");
        return buf[index];
    }


    const int& operator[](int index) const {
        if (!in_bounds(index)) throw std::out_of_range("Index out of bounds");
        return buf[index];
    }


    void fill(int val) {
        std::fill_n(buf, len, val);
    }

    friend void swap(Array& lhs, Array& rhs) noexcept {
        std::swap(lhs.len, rhs.len);
        std::swap(lhs.buf, rhs.buf);
    }

private:
    int len;
    int* buf;

    bool in_bounds(int index) const {
        return index >= 0 && index < len;
    }
};


inline std::ostream& operator<<(std::ostream& out, const Array& array) {
    std::ostringstream temp;
    temp << std::setprecision(2) << std::fixed << std::right;

    for (int i = 0; i < array.length(); ++i) {
        temp << std::setw(8) << array[i];
    }

    out << temp.str();
    return out;
}


inline std::istream& operator>>(std::istream& in, Array& array) {
    for (int i = 0; i < array.length(); ++i) {
        in >> array[i];
    }

    return in;
}

#endif