cmake_minimum_required(VERSION 3.10.2)

set(This sudokuTest)

project(${This} C CXX)

set(Sources sudokuTest.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC gtest_main sudoku)

add_test(NAME ${This} COMMAND ${This})