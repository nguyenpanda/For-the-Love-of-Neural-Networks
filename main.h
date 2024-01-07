//
// Created by Hà Tường Nguyên on 12/28/23.
//

#ifndef MATRIX_MAIN_H
#define MATRIX_MAIN_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <chrono>

#include "Color/color.h"
#include "Tensor/tensor.h"

using namespace color;

double executeTime(void (*func)(), bool secondUnit = false) {
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double precision = 1;
    if (secondUnit) {
        precision = 1e6;
    }

    return (double) duration.count() / precision;
}

void executeTime_dis(void (*func)(), bool secondUnit = false) {
    auto start = std::chrono::high_resolution_clock::now();

    func();

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    double precision = 1;
    std::string unit = " µs";
    if (secondUnit) {
        precision = 1e6;
        unit = " s";
    }

    std::cout << "Execute time: " << (double) duration.count() / precision << unit;
}

void hRule(int length) {
    std::cout << std::setw(length - 1) << std::setfill('-') << '-' << std::endl;
    std::cout << std::setw(0) << std::setfill(' ') << std::setprecision(6);
}

void print(std::string &message, char end = '\n') {
    std::cout << message << end;
}


#endif //MATRIX_MAIN_H
