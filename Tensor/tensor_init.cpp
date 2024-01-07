//
// Created by Hà Tường Nguyên on 12/29/23.
//

/**
 * @file tensor_init.cpp
 * @brief This file contains the implementation of the tensor class methods for creating and manipulating instances.
 *
 * @details
 * The tensor class provides functionalities for creating, manipulating, and invisibilities.
 */

#include "tensor.h"

namespace tns {

// Constructors
    template<typename type>
    tensor<type>::tensor()
            : _rows(1), _cols(1), _maxValue(0), _minValue(0) {
        _tns = new type *[1];
        _tns[0] = new type[0];
        _tns[0][0] = 0;
    }

    template<typename type>
    tensor<type>::tensor(size_t rows, size_t cols, type initData)
            : _rows(rows), _cols(cols), _maxValue(initData), _minValue(initData) {

        _tns = new type *[rows];

        for (int i = 0; i < rows; ++i) {
            _tns[i] = new type[cols];
            for (int j = 0; j < cols; ++j) {
                _tns[i][j] = initData;
            }
        }
    }

    template<typename type>
    tensor<type>::tensor(size_t rows, size_t cols, type minRange, type maxRange)
            : _rows(rows), _cols(cols) {

        std::random_device rd;
        std::mt19937 gen(rd());
        auto uniform = std::conditional_t<
                std::is_integral_v<type>,
                std::uniform_int_distribution<type>,
                std::uniform_real_distribution<type>
        >(minRange, maxRange);

        type temp;
        _tns = new type *[rows];

        for (int i = 0; i < rows; ++i) {
            _tns[i] = new type[cols];
            for (int j = 0; j < cols; ++j) {
                temp = uniform(gen);
                _tns[i][j] = temp;
                updateMinMaxValues(temp);
            }
        }

    }

    template<typename type>
    tensor<type>::tensor(type *array, size_t rows, size_t cols)
            : _rows(rows), _cols(cols) {

        _tns = new type *[rows];
        type temp;

        for (int i = 0; i < rows; ++i) {
            _tns[i] = new type[cols];
            for (int j = 0; j < cols; ++j) {
                temp = array[cols * i + j];
                updateMinMaxValues(temp);
                _tns[i][j] = temp;
            }
        }

    }

// Destructor
    template<typename type>
    tensor<type>::~tensor() = default;

// Getter, Setter
    template<typename type>
    size_t tensor<type>::row() const {
        return _rows;
    }

    template<typename type>
    size_t tensor<type>::col() const {
        return _cols;
    }

    template<typename type>
    type tensor<type>::max() const {
        return _maxValue;
    }

    template<typename type>
    type tensor<type>::min() const {
        return _minValue;
    }

    template<typename type>
    type **tensor<type>::pTensor() const {
        return _tns;
    }

// Private method
    // Update the private minValue and maxValue
    template<typename type>
    void tensor<type>::updateMinMaxValues(type value) {
        if (_maxValue < value) {
            _maxValue = value;
        }
        if (_minValue > value) {
            _minValue = value;
        }
    }
}

template
class tns::tensor<int>;

template
class tns::tensor<double>;

template
class tns::tensor<float>;
