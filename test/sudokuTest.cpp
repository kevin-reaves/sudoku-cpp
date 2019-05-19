#include <gtest/gtest.h>
#include "../solver/sudoku.hpp"
#include <iostream>


/*
 * Checking to make sure the rows in a solved grid are valid
 */
TEST(sudokuTests, rowTest){
    solver sudokuSolver;
    sudokuSolver.solveSudoku();
    gridLayout solved = sudokuSolver.returnArray();

    std::set<int> used;

    // Similar to validRow function from solver/sudoku.cpp
    for(int row=0; row<solved.size(); row++){
        for(int col=0; col<solved[row].size(); col++){
            // There shouldn't be any duplicate numbers in a row
            if(used.find(solved[row][col]) != used.end()){
                ASSERT_TRUE(false) << "There is a duplicate value in a solved grid row\n";
            }

            used.insert(solved[row][col]);
        }
        // Checking each row for duplicates, can reset the set at the end
        used.clear();
    }
}

/*
 * Checking to make sure the rows in a solved grid are valid
 */
TEST(sudokuTests, columnTest) {
    solver sudokuSolver;
    sudokuSolver.solveSudoku();
    gridLayout solved = sudokuSolver.returnArray();

    std::set<int> used;

    for (int col = 0; col < solved[0].size(); col++) {
        // Similar to validRow function from solver/sudoku.cpp
        for (int row = 0; row < solved.size(); row++) {
                // There shouldn't be any duplicate numbers in a row
                if(used.find(solved[row][col]) != used.end()) {
                    ASSERT_TRUE(false) << "There is a duplicate value in a solved grid column\n";
                }
                    used.insert(solved[row][col]);
            }
            // Checking each row for duplicates, can reset the set at the end
            used.clear();
        }
    }


/*
 * Checking to make sure no invalid numbers (outside 1-N) are in a solved grid
 * N is defined in solver/sudoku.hpp
 */
TEST(sudokuTests, validNumberTest){
    solver sudokuSolver;
    sudokuSolver.solveSudoku();
    gridLayout solved = sudokuSolver.returnArray();

    for(int row=0; row<solved.size(); row++){
        for(int col=0; col<solved[row].size(); col++){
            // There should only be numbers from 1-N in a grid
            if(solved[row][col] > N || solved[row][col] < 1){
                ASSERT_FALSE(true) << "There is a number outside 1-N in a solved grid\n";
            }
        }
    }
}