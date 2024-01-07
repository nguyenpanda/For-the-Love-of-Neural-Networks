//
// Created by Hà Tường Nguyên on 12/29/23.
//

/**
 * @brief This file contains all useful methods for training Neural Networks
 *
 * @methods
 * - display(int precision = 2, bool color = true) -> void
 *   | Print a colorful representation of the tensor.
 *
 * - det() -> typename
 *   | Calculate the determinant of the tensor.
 *
 * - f() -> tensor<typename>
 *   | COMING SOON! (Provide a brief description if possible.)
 *
 * - multiply(const tensor<typename> &rhs_tensor) -> tensor<typename>
 *   | Perform the Hadamard product with another tensor.
 *
 * - minor(size_t i, size_t j) -> tensor<typename>
 *   | Calculate the determinant of the subTensor obtained by removing the i-th row and j-th column.
 *
 * - subTensor(size_t i, size_t j) -> tensor<typename>
 *   | Create a new tensor by removing the i-th row and j-th column.
 *
 * - read_csv(const std::string &filename, int MAX_ROWS, int MAX_COLS, int precision = 5) -> tensor<double>
 *   | Create a tensor from a CSV file with specified maximum rows and columns.
 *
 * - T() -> tensor<typename>
 *   | Return the transpose of the tensor.
 **/

#include "tensor.h"

namespace tns {

    // Display tensor
    template<typename type>
    void tensor<type>::display(int precision, bool color) const {
        float delta = (_maxValue - _minValue > 0) ? (_maxValue - _minValue) / 7.0 : 1;

        int padding = (std::is_same<type, int>::value) ? 3 : 4; // including space(2), sign-(1), decimal dot(0 or 1)
        padding -= (_minValue > 0);
        precision = (std::is_same<type, int>::value) ? 0 : precision;

        type numBeforeDot = std::max(std::abs(_maxValue), std::abs(_minValue));
        type digits = std::log10(std::max(numBeforeDot, static_cast<type>(1))) + 1; // number before dot

        int width = static_cast<int>(digits + padding + precision);

        std::cout << std::setprecision(precision) << std::fixed;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {

                if (color) {
                    std::cout << color::getColorConstant(round((_tns[i][j] - _minValue) / (delta)));
                }

                std::cout << std::setw(width) << _tns[i][j] << color::RESET;
            }
            std::cout << '\n';
        }

        std::cout << std::setw(0) << std::setfill(' ') << std::setprecision(6);
    }

    // Determinate
    template<typename type>
    type tensor<type>::det() {
        if (_rows != _cols) {
            std::ostringstream message;
            message << "Matrix shape mismatch (det()): (" << _rows << ", " << _cols << ") is not a square matrix";
            throw NotSquareException(message.str(), _rows, _cols);
        }

        if (_rows == 2) {
            return _tns[0][0] * _tns[1][1] - _tns[1][0] * _tns[0][1];
        }

        type result = 0;
        for (int i = 0; i < _cols; ++i) {
            tensor<type> tempTensor = subTensor(0, i);
            result += std::pow((-1), (i)) * _tns[0][i] * tempTensor.det();
        }

        return result;
    }

    // Element-wise function || COMING SOON! Use elementWise() instead!
    template<typename type>
    tensor<type> tensor<type>::f() {
        return tensor<type>(1, 2);
    }

    // Hadamard product
    template<typename type>
    tensor<type> tensor<type>::multiply(const tensor<type> &rhs_tensor) const {
        if (_rows != rhs_tensor._rows || _cols != rhs_tensor._cols) {
            std::ostringstream message;
            message << "\nMatrix shape mismatch (^ element-wise production): (" << _rows << ", " << _cols << ") vs ("
                    << rhs_tensor._rows << ", " << rhs_tensor._cols << ")";
            throw ShapeMismatchException(message.str(), _rows, _cols, rhs_tensor._rows, rhs_tensor._cols);
        }

        tensor<type> result(_rows, _cols);
        type temp;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                temp = _tns[i][j] * rhs_tensor._tns[i][j];
                result.updateMinMaxValues(temp);
                result._tns[i][j] = temp;
            }
        }

        return result;
    }

    // Minor
    template<typename type>
    type tensor<type>::minor(size_t i, size_t j) {
        if (i >= _rows || j >= _cols) {
            std::ostringstream message;
            message << "\nMatrix out of range: minor of matrix(" << i << ", " << j << ") not belongs to matrix("
                    << _rows << ", " << _cols << ")";
            throw OutOfRangeException(message.str(), _rows, _cols);
        }

        return subTensor(i, j).det();
    }

    // Sub-tensor
    template<typename type>
    tensor<type> tensor<type>::subTensor(size_t i, size_t j) {
        if (i >= _rows || j >= _cols) {
            std::ostringstream message;
            message << "\nMatrix out of range: subTensor(" << i << ", " << j << ") not belongs to matrix(" << _rows
                    << ", " << _cols << ")";
            throw OutOfRangeException(message.str(), _rows, _cols);
        }

        tensor<type> result(_rows - 1, _cols - 1);

        for (size_t k = 0, resultRow = 0; k < _rows; ++k) {
            if (k == i) continue;

            for (size_t l = 0, resultCol = 0; l < _cols; ++l) {
                if (l == j) continue;

                result._tns[resultRow][resultCol++] = _tns[k][l];
                result.updateMinMaxValues(_tns[k][l]);
            }

            ++resultRow;
        }

        return result;
    }

    // Read data from a CSV file
    template<typename type>
    tensor<type>
    tensor<type>::read_csv(const std::string &filename, const int &MAX_ROWS, const int &MAX_COLS, int precision) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::string message = "\nError opening file (tns::tensor::read_csv()): " + filename;
            throw std::runtime_error(message);
        }

        tensor<type> output(MAX_ROWS, MAX_COLS);

        int numRows = 0, numCols = 0;
        double decimal = std::pow(10, precision);
        std::string line, string_cell;
        type num_cell;

        while (std::getline(file, line, '\n') && numRows < MAX_ROWS) {
            std::istringstream iss(line);

            while (std::getline(iss, string_cell, ',') && numCols < MAX_COLS) {
                num_cell = std::round(std::stod(string_cell) * decimal) / decimal;
                output.pTensor()[numRows][numCols++] = num_cell;
                output.updateMinMaxValues(num_cell);
            }

            numCols = 0;
            ++numRows;
        }

        file.close();

        return output;
    }

    // Transpose
    template<typename type>
    tensor<type> tensor<type>::T() {
        #pragma clang diagnostic push
        #pragma ide diagnostic ignored "ArgumentSelectionDefects"
        tensor<type> result(_cols, _rows);
        #pragma clang diagnostic pop

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result._tns[j][i] = _tns[i][j];
            }
        }

        result._minValue = min();
        result._maxValue = max();

        return result;
    }

}

template
class tns::tensor<int>;

template
class tns::tensor<double>;

template
class tns::tensor<float>;