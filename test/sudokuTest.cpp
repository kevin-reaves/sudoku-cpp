#include <gtest/gtest.h>
#include "../solver/sudoku.hpp"

struct sudokuTests : testing::Test{
    gridLayout grid = {{{3, 0, 6, 5, 0, 8, 4, 0, 0},
                               {5, 2, 0, 0, 0, 0, 0, 0, 0},
                               {0, 8, 7, 0, 0, 0, 0, 3, 1},
                               {0, 0, 3, 0, 1, 0, 0, 8, 0},
                               {9, 0, 0, 8, 6, 3, 0, 0, 5},
                               {0, 5, 0, 0, 9, 0, 6, 0, 0},
                               {1, 3, 0, 0, 0, 0, 2, 5, 0},
                               {0, 0, 0, 0, 0, 0, 0, 7, 4},
                               {0, 0, 5, 2, 0, 6, 3, 0, 0}}};

};

/*
 * Checking to make sure the rows in a solved grid are valid
 */
TEST_F(sudokuTests, rowTests){
    solver sudokuSolver(grid);
    sudokuSolver.solveSudoku();
    gridLayout solved = sudokuSolver.returnArray();

    std::set<int> used;

    // Similar to validRow function from solver/sudoku.cpp
    for(int row=0; row<solved.size(); row++){
        for(int col=0; col<solved[row].size(); col++){
            // There shouldn't be any zeroes in a solved grid
            ASSERT_NE(solved[row][col], 0) << "There is a zero in a solved grid\n";

            if(used.find(solved[row][col]) != used.end()){
                ASSERT_TRUE(false) << "There is a duplicate value in a solved grid\n";
            }

            used.insert(solved[row][col]);
        }
        // Checking each row for duplicates, can reset the set at the end
        used.clear();
    }


}