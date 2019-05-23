cmake_minimum_required(VERSION 3.10.2)

set(This sudoku)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers solver/sudoku.hpp)

set(Sources solver/sudoku.cpp)

add_library(${This} STATIC ${Sources} ${Headers})

add_executable(main main.cpp)

add_subdirectory(test)