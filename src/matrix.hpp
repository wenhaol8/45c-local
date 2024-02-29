#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "array.hpp"
#include <iostream>

template <typename T>
class Matrix {
public:

    Matrix() : rows(0), cols(0), data() {}


    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows) {
        for (int i = 0; i < rows; ++i) {
            data[i] = Array<T>(cols);
        }
    }


    Array<T>& operator[](int row) {
        return data[row];
    }
    const Array<T>& operator[](int row) const {
        return data[row];
    }


    int num_rows() const { return rows; }
    int num_cols() const { return cols; }


    void fill(const T& val) {
        for (int i = 0; i < rows; ++i) {
            data[i].fill(val);
        }
    }


    template <typename Fn>
    void fill_with_fn(Fn fn) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                data[i][j] = fn(i, j);
            }
        }
    }

private:
    int rows, cols;
    Array<Array<T>> data;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    out << std::fixed << std::setprecision(2);
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            out << std::setw(8) << matrix[i][j]; // Again, adjust the width as needed
            if (j < matrix.num_cols() - 1) out << " "; // Space between elements, except after the last in a row
        }
        if (i < matrix.num_rows() - 1) out << "\n"; // Newline after each row, except after the last
    }
    return out;
}

template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    for (int i = 0; i < matrix.num_rows(); ++i) {
        for (int j = 0; j < matrix.num_cols(); ++j) {
            in >> matrix[i][j];
        }
    }
    return in;
}

#endif