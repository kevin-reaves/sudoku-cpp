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
TEST_F(sudokuTests, rowTest){
    solver sudokuSolver(grid);
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
TEST_F(sudokuTests, columnTest) {
    solver sudokuSolver(grid);
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
TEST_F(sudokuTests, validNumberTest){
    solver sudokuSolver(grid);
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