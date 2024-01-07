//
// Created by Hà Tường Nguyên on 12/28/23.
//

#ifndef MATRIX_TENSOR_H
#define MATRIX_TENSOR_H

#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <random>
#include <limits>

#include "Exception/tensor_error_programing.h"
#include "../Color/color.h"

namespace tns {

    /**
     * @brief A generic tensor class template representing a mathematical tensor.
     *
     * This class provides functionalities for tensor creation, manipulation, and various operations.
     * It supports element-wise operations, matrix multiplication, and basic linear algebra operations.
     *
     * @tparam type: The type of elements stored in the tensor.
     */
    template<typename type>
    class tensor {
        size_t _rows{}, _cols{};
        type _maxValue = -std::numeric_limits<type>::infinity();
        type _minValue = std::numeric_limits<type>::infinity();
        type **_tns;

    public:
    //  tensor_init.cpp/Constructor
        // Create (0, 0) tensor
        tensor();

        // Initialize constructors
        tensor(size_t rows, size_t cols, type initData = 0);

        // Random constructor
        tensor(size_t rows, size_t cols, type minRange, type maxRange);

        // From array constructor
        tensor(type *array, size_t rows, size_t cols = 1);

        //  tensor_init.cpp/Destructor
        virtual ~tensor();

    //  tensor_init.cpp/Getter, Setter
        [[nodiscard]] [[maybe_unused]] size_t row() const;

        [[nodiscard]] [[maybe_unused]] size_t col() const;

        [[nodiscard]] [[maybe_unused]] type max() const;

        [[nodiscard]] [[maybe_unused]] type min() const;

        [[nodiscard]] [[maybe_unused]] type **pTensor() const;

    // tensor_operators.cpp/Overload operators
        // Getting element
        type operator()(size_t i, size_t j) const;

        // Getting column
        tensor operator[](size_t j) const;

        // Matrix multiplication
        tensor operator*(const tensor<type> &rhs_tensor) const;

        // Binary operation
        tensor operator+(const tensor<type> &rhs_tensor) const;

        tensor operator-(const tensor<type> &rhs_tensor) const;

        tensor operator/(const tensor<type> &rhs_tensor) const;

    // Scalar/Element-wise operators
        tensor operator+(const type &num) const;

        tensor operator-(const type &num) const;

        tensor operator*(const type &num) const;

        tensor operator/(const type &num) const;

        tensor operator^(const type &num) const;

    // tensor.cpp/Public method
        /**
        * @brief Display the tensor to the standard output.
        *
        * @param precision The number of decimal places to display (default is 2).
        * @param color Whether to display the tensor with color highlights (default is true).
        */
        void display(int precision = 2, bool color = true) const; // Print the tensor

        // Determinate
        /**
        * @brief Calculate the determinant of the square tensor.
        *
        * @return The determinant of the tensor.
        */
        type det();

        /**
        * @brief Apply an element-wise function to each element of the tensor.
        *
        * @tparam Function The type of the lambda function to be applied.
        * @param func The element-wise function.
        * @return A new tensor with the result of the element-wise operation.
        */
        template<typename Function>
        tensor elementWise(Function func) const {
            return applyOperation(0,
                                  [func](type x, type /*num*/) { return func(x); }
            );
        }

        // Element-wise function
        /**
         * COMING SOON!
         * @return
         */
        static tensor f();

        // Binary-wise operation/Hadamard product
        tensor multiply(const tensor<type> &rhs_tensor) const;

        // Creat a matrix that remove row=i, col=j
        type minor(size_t i, size_t j);

        // Transpose
        tensor T();

        // Getting the sub-tensor from original tensor by removing the row (i) and col (j)
        /**
        * @brief Create a matrix that removes the specified row and column.
        *
        * @param i The index of the row to be removed.
        * @param j The index of the column to be removed.
        * @return A new tensor with the specified row and column removed.
        */
        tensor subTensor(size_t i, size_t j);

        template<typename rhsType>
        bool sameSize(tensor<rhsType> &rhs_tensor) {
            if (rhs_tensor.row() == this->_rows && rhs_tensor.col() == this->_cols) {
                return true;
            } else {
                return false;
            }
        }

        // Creating from the CSV file
        /**
        * @brief Read a tensor from a CSV file.
        *
        * @param filename The name of the CSV file.
        * @param MAX_ROWS The maximum number of rows to read from the file.
        * @param MAX_COLS The maximum number of columns to read from the file.
        * @param precision The precision of the numbers in the CSV file (default is 5).
        * @return The tensor read from the CSV file.
        */
        static tensor<type>
        read_csv(const std::string &filename, const int &MAX_ROWS, const int &MAX_COLS, int precision = 5);

    private:
        /**
        * @brief Update the minimum and maximum values of the tensor.
        *
        * @param value The value to compare and update the minimum and maximum values.
        */
        void updateMinMaxValues(type value);

        /**
        * @brief Apply a binary operation to the tensor.
        *
        * @param num The scalar operand.
        * @param operation The binary operation to be applied.
        * @return A new tensor with the result of the binary operation.
        */
        tensor<type> applyOperation(type num, std::function<type(type, type)> operation) const;

    };

} // tns

template<typename type>
tns::tensor<type> operator+(type num, const tns::tensor<type> &tensor) {
    return tensor + num;
}

template<typename type>
tns::tensor<type> operator-(type num, const tns::tensor<type> &tensor) {
    return tensor - num;
}

template<typename type>
tns::tensor<type> operator*(type num, const tns::tensor<type> &tensor) {
    return tensor * num;
}

template<typename type>
tns::tensor<type> operator/(type num, const tns::tensor<type> &tensor) {
    return tensor / num;
}

template<typename type>
std::ostream &operator<<(std::ostream &COUT, tns::tensor<type> &tensor) {
    const auto &tns = tensor.pTensor();
    const type min = tensor.min();
    const type max = tensor.max();
    const int row = tensor.row();
    const int col = tensor.col();
    const int precision = static_cast<int>(std::cout.precision());
    const float delta = (max - min > 0) ? (max - min) / 7.0 : 1.0;

    // including space(2), sign+-(1), decimal and dot(0 or 4)
    int k = (std::is_same<type, int>::value) ? 3 : (4 + precision);
    k -= (min > 0);

    type numBeforeDot = std::max(std::abs(max), std::abs(min));
    type digits = std::log10(std::max(numBeforeDot, static_cast<type>(1))) + 1; // number before dot

    int width = static_cast<int>(digits + k);
    COUT << std::setprecision(precision) << std::fixed;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            COUT << color::getColorConstant(round((tns[i][j] - min) / delta))
                 << std::setw(width) << tns[i][j] << color::RESET;
        }
        COUT << '\n';
    }

//    std::cout << std::setw(0) << std::setfill(' ') << std::setprecision(6);

    return COUT;
}

#endif //MATRIX_TENSOR_H