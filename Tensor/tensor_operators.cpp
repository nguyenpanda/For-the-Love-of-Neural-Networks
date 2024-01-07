//
// Created by Hà Tường Nguyên on 12/28/23.
//

#include "tensor.h"

namespace tns {
// Overload operators
    // Getting element
    template<typename type>
    type tensor<type>::operator()(size_t i, size_t j) const {
        if (i >= _rows || j >= _cols) {
            std::ostringstream message;
            message << "\nMatrix out of range: Position(" << i << ", " << j << ") not belongs to matrix(" << _rows
                    << ", " << _cols << ")";
            throw OutOfRangeException(message.str(), _rows, _cols);
        }

        return _tns[i][j];
    }

    // Getting column
    template<typename type>
    tensor<type> tensor<type>::operator[](size_t j) const {
        if (j >= _cols) {
            std::ostringstream message;
            message << "\nMatrix out of range: Column[" << j << "] not belongs to matrix(" << _rows << ", " << _cols
                    << ")";
            throw OutOfRangeException(message.str(), _rows, _cols);
        }

        tensor<type> result(_rows, 1);

        for (int i = 0; i < _rows; ++i) {
            result._tns[i][0] = _tns[i][j];
            result.updateMinMaxValues(_tns[i][j]);
        }

        return result;
    }

    // Matrix multiplication
    template<typename type>
    tensor<type> tensor<type>::operator*(const tensor<type> &rhs_tensor) const {
        if (_cols != rhs_tensor._rows) {
            std::ostringstream message;
            message << "\nMatrix shape mismatch (* matrix multiplication): (" << _rows << ", " << _cols << ") vs ("
                    << rhs_tensor._rows << ", " << rhs_tensor._cols << ")";
            throw ShapeMismatchException(message.str(), _rows, _cols, rhs_tensor._rows, rhs_tensor._cols);
        }

        tensor<type> result(_rows, rhs_tensor._cols);

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < rhs_tensor._cols; ++j) {
                type dotProduct = 0;
                for (int k = 0; k < _cols; ++k) {
                    dotProduct += _tns[i][k] * rhs_tensor._tns[k][j];
                }
                result._tns[i][j] = dotProduct;
                result.updateMinMaxValues(dotProduct);
            }
        }

        return result;
    }

    // Binary operation
    template<typename type>
    tensor<type> tensor<type>::operator+(const tensor<type> &rhs_tensor) const {
        if (_rows != rhs_tensor._rows || _cols != rhs_tensor._cols) {
            std::ostringstream message;
            message << "\nMatrix shape mismatch (+ element-wise addition): (" << _rows << ", " << _cols << ") vs ("
                    << rhs_tensor._rows << ", " << rhs_tensor._cols << ")";
            throw ShapeMismatchException(message.str(), _rows, _cols, rhs_tensor._rows, rhs_tensor._cols);
        }

        tensor<type> result(_rows, _cols);
        type temp;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                temp = _tns[i][j] + rhs_tensor._tns[i][j];
                result.updateMinMaxValues(temp);
                result._tns[i][j] = temp;
            }
        }

        return result;
    }

    template<typename type>
    tensor<type> tensor<type>::operator-(const tensor<type> &rhs_tensor) const {
        if (_rows != rhs_tensor._rows || _cols != rhs_tensor._cols) {
            std::ostringstream message;
            message << "\nMatrix shape mismatch (- element-wise subtraction): (" << _rows << ", " << _cols << ") vs ("
                    << rhs_tensor._rows << ", " << rhs_tensor._cols << ")";
            throw ShapeMismatchException(message.str(), _rows, _cols, rhs_tensor._rows, rhs_tensor._cols);
        }

        tensor<type> result(_rows, _cols);
        type temp;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                temp = _tns[i][j] - rhs_tensor._tns[i][j];
                result.updateMinMaxValues(temp);
                result._tns[i][j] = temp;
            }
        }

        return result;
    }

    template<typename type>
    tensor<type> tensor<type>::operator/(const tensor<type> &rhs_tensor) const {
        if (_rows != rhs_tensor._rows || _cols != rhs_tensor._cols) {
            std::ostringstream message;
            message << "\nMatrix shape mismatch (/ element-wise division): (" << _rows << ", " << _cols << ") vs ("
                    << rhs_tensor._rows << ", " << rhs_tensor._cols << ")";
            throw ShapeMismatchException(message.str(), _rows, _cols, rhs_tensor._rows, rhs_tensor._cols);
        }

        tensor<type> result(_rows, _cols);
        type temp;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                temp = _tns[i][j] / rhs_tensor._tns[i][j];
                result.updateMinMaxValues(temp);
                result._tns[i][j] = temp;
            }
        }

        return result;
    }

    // Scalar/Element-wise operators
    template<typename type>
    tensor<type> tensor<type>::operator+(const type &num) const {
        return applyOperation(num, std::plus<type>());
    }

    template<typename type>
    tensor<type> tensor<type>::operator-(const type &num) const {
        return applyOperation(num, std::minus<type>());
    }

    template<typename type>
    tensor<type> tensor<type>::operator*(const type &num) const {
        return applyOperation(num, std::multiplies<type>());
    }

    template<typename type>
    tensor<type> tensor<type>::operator/(const type &num) const {
        return applyOperation(num, std::divides<type>());
    }

    template<typename type>
    tensor<type> tensor<type>::operator^(const type &num) const {
        auto powOperation = [](type a, type b) {
            return std::pow(a, b);
        };

        return applyOperation(num, powOperation);
    }

// Private method
    template<typename type>
    tensor<type> tensor<type>::applyOperation(type num, std::function<type(type, type)> operation) const {
        tensor<type> result(_rows, _cols);
        result._minValue = _minValue;
        result._maxValue = _maxValue;

        for (int i = 0; i < _rows; ++i) {
            for (int j = 0; j < _cols; ++j) {
                result._tns[i][j] = operation(_tns[i][j], num);
                result.updateMinMaxValues(result._tns[i][j]);
            }
        }

        return result;
    }

} // tns

template
class tns::tensor<int>;

template
class tns::tensor<double>;

template
class tns::tensor<float>;