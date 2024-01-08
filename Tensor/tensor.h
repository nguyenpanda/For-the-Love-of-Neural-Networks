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
        /**
         * @brief Default constructor to create a (1x1) tensor with a value of 0.
         */
        tensor();

        // Initialize constructors
        /**
         * @brief Constructor to initialize a tensor with specified dimensions and initial data.
         *
         * @param rows The number of rows in the tensor.
         * @param cols The number of columns in the tensor.
         * @param initData The initial value to fill the tensor (default is 0).
         */
        tensor(size_t rows, size_t cols, type initData = 0);

        // Random constructor
        /**
         * @brief Constructor to create a tensor with random values within a specified range.
         *
         * @param rows The number of rows in the tensor.
         * @param cols The number of columns in the tensor.
         * @param minRange The minimum value for the random range.
         * @param maxRange The maximum value for the random range.
         */
        tensor(size_t rows, size_t cols, type minRange, type maxRange);

        // From array constructor
        /**
         * @brief Constructor to create a tensor from a one-dimensional array.
         *
         * @param array Pointer to the one-dimensional array.
         * @param rows The number of rows in the tensor.
         * @param cols The number of columns in the tensor.
         */
        tensor(type *array, size_t rows, size_t cols = 1);

        //  tensor_init.cpp/Destructor
        virtual ~tensor();

    //  tensor_init.cpp/Getter, Setter
        /**
         * @brief Get the number of rows in the tensor.
         *
         * @return The number of rows.
         */
        [[nodiscard]] [[maybe_unused]] size_t row() const;

        /**
         * @brief Get the number of columns in the tensor.
         *
         * @return The number of columns.
         */
        [[nodiscard]] [[maybe_unused]] size_t col() const;

        /**
         * @brief Get the maximum value in the tensor.
         *
         * @return The maximum value.
         */
        [[nodiscard]] [[maybe_unused]] type max() const;

        /**
         * @brief Get the minimum value in the tensor.
         *
         * @return The minimum value.
         */
        [[nodiscard]] [[maybe_unused]] type min() const;

        /**
         * @brief Get the pointer to the tensor data.
         *
         * @return The pointer to the tensor data.
         */
        [[nodiscard]] [[maybe_unused]] type **pTensor() const;

    // tensor_operators.cpp/Overload operators
        // Getting element
        /**
         * @brief Get the element at the specified row and column.
         *
         * @param i The row index.
         * @param j The column index.
         * @return The element at the specified position.
         */
        type operator()(size_t i, size_t j) const;

        // Getting column
        /**
         * @brief Get a column of the tensor.
         *
         * @param j The column index.
         * @return A tensor representing the specified column.
         */
        tensor operator[](size_t j) const;

        // Matrix multiplication
        /**
         * @brief Multiply the tensor with another tensor using matrix multiplication. Noted that
         * this operator is different from multiply method.
         *
         * @param rhs_tensor The right-hand side tensor.
         * @return The result of a NEW tensor.
         */
        tensor operator*(const tensor<type> &rhs_tensor) const;

        // Binary operation
        /**
         * @brief Add another tensor to this tensor.
         *
         * @param rhs_tensor The right-hand side tensor.
         * @return The result of a NEW tensor.
         */
        tensor operator+(const tensor<type> &rhs_tensor) const;

        /**
         * @brief Subtract another tensor from this tensor.
         *
         * @param rhs_tensor The right-hand side tensor.
         * @return The result of a NEW tensor.
         */
        tensor operator-(const tensor<type> &rhs_tensor) const;

        /**
         * @brief Divide this tensor by another tensor element-wise.
         *
         * @param rhs_tensor The right-hand side tensor.
         * @return The result of a NEW tensor.
         */
        tensor operator/(const tensor<type> &rhs_tensor) const;

    // Scalar/Element-wise operators
        /**
         * @brief Add a scalar value to each element of the tensor.
         *
         * @param num The scalar value to add.
         * @return The result of a NEW tensor.
         */
        tensor operator+(const type &num) const;

        /**
         * @brief Subtract a scalar value from each element of the tensor.
         *
         * @param num The scalar value to subtract.
         * @return The result of a NEW tensor.
         */
        tensor operator-(const type &num) const;

        /**
         * @brief Multiply each element of the tensor by a scalar value.
         *
         * @param num The scalar value to multiply.
         * @return The result of a NEW tensor.
         */
        tensor operator*(const type &num) const;

        /**
         * @brief Divide each element of the tensor by a scalar value.
         *
         * @param num The scalar value to divide by.
         * @return The result of a NEW tensor.
         */
        tensor operator/(const type &num) const;

        /**
         * @brief Raise each element of the tensor to the power of a scalar value.
         *
         * @param num The scalar value representing the exponent.
         * @return The result of a NEW tensor.
         */
        tensor operator^(const type &num) const;

    // tensor.cpp/Public method
        // Print the tensor
        /**
         * @brief Displays the tensor on the standard output.
         *
         * This method prints the tensor to the standard output, allowing customization of the display format.
         *
         * @details
         * - The precision parameter determines the number of decimal places to display (default is 2). Additionally,
         * the color parameter, when set to true (default), highlights the tensor values using a color scale.
         * - The color scale divides the range between Max_value and Min_value into 7 segments, ranging from
         * White < Magenta < Cyan < Blue < Green < Yellow < Red.
         *
         * @param precision The number of decimal places to display (default is 2).
         * @param color Whether to display the tensor with color highlights (default is true).
         */
        void display(int precision = 2, bool color = true) const;

        // Determinate
        /**
        * @brief Calculate the determinant of the square tensor.
        *
        * @return The determinant of the tensor.
        */
        type det();

        // Element-wise application
        /**
         * @brief Applies an element-wise operation to each element of the tensor.
         *
         * This template function takes a unary function and applies it to each element of the tensor.
         * The resulting tensor has the same dimensions as the original tensor, where each element is the
         * result of applying the provided function to the corresponding element of the original tensor.
         *
         * @tparam Function The unary function to be applied element-wise.
         * @param func The unary function taking a single argument and returning the result.
         * @return A new tensor resulting from applying the element-wise operation.
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
         * Use elementWise() method instead!
         * @brief
         * @return
         */
        static tensor f();

        // Binary-wise operation/Hadamard product
        /**
         * @brief Performs a binary-wise operation, also known as the Hadamard product, with another tensor.
         *
         * This method multiplies each corresponding element of the current tensor with the corresponding
         * element of the given tensor, resulting in a new tensor of the same dimensions.
         *
         * @param rhs_tensor The tensor to perform the binary-wise operation with.
         * @return A new tensor representing the result of the binary-wise operation.
         */
        tensor multiply(const tensor<type> &rhs_tensor) const;

        // Create a matrix by removing row=i, col=j
        /**
         * @brief Generates a new matrix by removing a specified row and column.
         *
         * This method creates a new matrix by excluding the specified row (indexed by i) and column
         * (indexed by j) from the current matrix. The resulting matrix is of reduced size.
         *
         * @param i The index of the row to be removed. It must satisfy the condition 0 <= i < MAX_ROWS.
         * @param j The index of the column to be removed. It must satisfy the condition 0 <= j < MAX_COLS.
         * @return The minor matrix without the specified row and column.
         */
        type minor(size_t i, size_t j);

        // Transpose
        /**
         * @brief Computes the transpose of the current tensor.
         *
         * This method returns a new tensor where the rows and columns of the original tensor are swapped.
         * The resulting tensor has dimensions opposite to the original tensor.
         *
         * @return The transposed tensor.
         */
        tensor T();

        // Getting the sub-tensor from original tensor by removing the row (i) and col (j)
        /**
         * @brief Extracts a sub-tensor by removing the specified row and column.
         *
         * This method creates and returns a new tensor that represents a sub-region of the current tensor.
         * The sub-tensor is obtained by excluding the specified row (indexed by i) and column (indexed by j)
         * from the original tensor.
         *
         * @param i The index of the row to be removed from the sub-tensor.
         * @param j The index of the column to be removed from the sub-tensor.
         * @return The sub-tensor obtained by removing the specified row and column.
         */
        tensor subTensor(size_t i, size_t j);

        /**
         * @brief Checks if the dimensions of the current tensor are the same as another tensor.
         *
         * This template method compares the dimensions (number of rows and columns) of the current tensor
         * with those of the specified tensor (`rhs_tensor`). It returns true if the dimensions are the same
         * and false otherwise.
         *
         * @tparam rhsType The data type of the elements in the specified tensor.
         * @param rhs_tensor The tensor to compare sizes with.
         * @return True if the row and column are the same, false otherwise.
         */
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
         * @brief Reads a tensor from a CSV file.
         *
         * This static method reads data from a CSV file and creates a tensor. It allows specifying the maximum
         * number of rows and columns to read from the file. The precision parameter determines the precision of the
         * numbers in the CSV file (default is 5).
         *
         * @param filename The name of the CSV file.
         * @param MAX_ROWS The maximum number of tensor row.
         * @param MAX_COLS The maximum number of tensor column.
         * @param precision The precision of the numbers in the CSV file (default is 5).
         * @return The tensor read from the CSV file.
         *
         * @note If the file has fewer rows or columns than specified by MAX_ROWS or MAX_COLS, the remaining elements
         * will be set to 0. If the file contains more rows or columns, excess data will be ignored.
         * Malformed or incomplete CSV files may result in unexpected behavior.
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