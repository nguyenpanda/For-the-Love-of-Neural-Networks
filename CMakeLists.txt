cmake_minimum_required(VERSION 3.26)
project(Tensor)

set(CMAKE_CXX_STANDARD 23)

add_executable(Tensor main.cpp
        main.h

        Tensor/tensor.h
        Tensor/tensor_init.cpp
        Tensor/tensor.cpp
        Tensor/tensor_operators.cpp

        Tensor/Exception/tensor_error_programing.cpp
        Tensor/Exception/tensor_error_programing.h

        Color/color.cpp
        Color/color.h)
