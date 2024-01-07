//
// Created by Hà Tường Nguyên on 12/30/23.
//

#ifndef MATRIX_TENSOR_ERROR_PROGRAMING_H
#define MATRIX_TENSOR_ERROR_PROGRAMING_H

#include "../tensor.h"
#include <stdexcept>

namespace tns {

    class ShapeMismatchException : public std::runtime_error {
    private:
        size_t rows1, cols1, rows2, cols2;
    public:
        ShapeMismatchException(const std::string &message, size_t rows1, size_t cols1, size_t rows2, size_t cols2)
                : std::runtime_error(message), rows1(rows1), cols1(cols1), rows2(rows2), cols2(cols2) {}
    };


    class NotSquareException : public std::runtime_error {
    private:
        size_t row, col;
    public:
        NotSquareException(const std::string &message, size_t row, size_t col)
                : std::runtime_error(message), row(row), col(col) {}
    };


    class OutOfRangeException : public std::out_of_range {
    private:
        size_t row, col;
    public:
        OutOfRangeException(const std::string &message, size_t row, size_t col)
                : std::out_of_range(message), row(row), col(col) {}
    };

}
#endif //MATRIX_TENSOR_ERROR_PROGRAMING_H
