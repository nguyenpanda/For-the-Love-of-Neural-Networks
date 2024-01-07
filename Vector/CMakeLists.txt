cmake_minimum_required(VERSION 3.26)
project(Coordinate)

set(CMAKE_CXX_STANDARD 17)

add_executable(Coordinate main.cpp
        Vector.cpp
        Vector.h)
