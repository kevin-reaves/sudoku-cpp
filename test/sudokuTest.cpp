#include <gtest/gtest.h>
#include "../solver/sudoku.hpp"
#include <iostream>

/*
 * The testIsValid test group checks the 'isValidRow', 'isValidCol', and 'isValidBox' functions (called by constructor)
 * We're looking for duplicate numbers or invalid (outside 0-9) in a row, column, or 3x3 box
 * NOTE: Numbers outside the 0-9 range are checked by the 'isValidBox' function
 */

// Checks to make sure duplicate numbers in a row are caught
TEST(testIsValid, rowDuplicate){
    gameBoard duplicateNumbers = {{
        {5, 5, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    }};

    try{
        solver sudokuSolver(duplicateNumbers);
        ASSERT_TRUE(false) << "The constructor was supposed to fail here because of duplicates in a row";
    } catch(const std::invalid_argument& e){
        //pass, constructor is supposed to fail
    }
}

// Checks to make sure duplicate numbers in a column are caught
TEST(testIsValid, colDuplicate){
    gameBoard duplicateNumbers = {{
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {5, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    }};

    try{
        solver sudokuSolver(duplicateNumbers);
        ASSERT_TRUE(false) << "The constructor was supposed to fail here because of duplicates in a column";
    } catch(const std::invalid_argument& e){
        //pass, constructor is supposed to fail
    }
}

// Checks to make sure duplicate numbers in a 9x9 grid are caught
TEST(testIsValid, gridDuplicate){
    gameBoard duplicateNumbers = {{
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 6, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    }};

    try{
        solver sudokuSolver(duplicateNumbers);
        ASSERT_TRUE(false) << "The constructor was supposed to fail here because of duplicates in a grid";
    } catch(const std::invalid_argument& e){
        //pass, constructor is supposed to fail
    }
}

// Checks to make sure invalid numbers (outside 0-9) are caught
TEST(testIsValid, invalidNumbers){
    gameBoard tooSmall = {{
        {-1, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    }};

    try{
        solver sudokuSolver(tooSmall);
        ASSERT_TRUE(false) << "The constructor was supposed to fail here because of a number that was too small";
    } catch(const std::invalid_argument& e){
        //pass, constructor is supposed to fail
    }

    gameBoard tooLarge = {{
        {BOARDSIZE+1, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 0}
    }};

    try{
        solver sudokuSolver(tooLarge);
        ASSERT_TRUE(false) << "The constructor was supposed to fail here because of a number that was too large";
    } catch(const std::invalid_argument& e){
        //pass, constructor is supposed to fail
    }
}

/*
 * Checks to make sure a solved grid returns itself
 */
TEST(sudokuTests, solvedGrid){
    solver sudokuSolver;
    sudokuSolver.solveSudoku();
    gameBoard solvedA = sudokuSolver.returnBoard();

    gameBoard solvedB;

    // Manual deep copy
    for(int row=0; row<BOARDSIZE; row++){
        for(int col=0; col<BOARDSIZE; col++){
            solvedB[row][col] = solvedA[row][col];
        }
    }

    solver alreadySolved(solvedB);
    alreadySolved.solveSudoku();
    solvedB = alreadySolved.returnBoard();

    for(int row=0; row<BOARDSIZE; row++){
        for(int col=0; col<BOARDSIZE; col++){
            EXPECT_EQ(solvedA[row][col], solvedB[row][col]) << "A solved array changes when being sent back through\n";
        }
    }
}

/*
 * Credit to http://sudopedia.enjoysudoku.com/Invalid_Test_Cases.html
 * The unsolvable group checks to make sure 'unsolvable' boards don't return solutions
 * Honestly, I should have written a web scraper for this, but it was faster to type three in by hand
 */

// From 'Unsolvable Square', row 5 should be invalid
TEST(unsolvable, unsolvableRow){
    gameBoard unsolvableRow = {{
        {0, 0, 9, 0, 2, 8, 7, 0, 0},
        {8, 0, 6, 0, 0, 4, 0, 0, 5},
        {0, 0, 3, 0, 0, 0, 0, 0, 4},
        {6, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 0, 7, 1, 3, 4, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2},
        {3, 0, 0, 0, 0, 0, 5, 0, 0},
        {9, 0, 0, 4, 0, 0, 8, 0, 7},
        {0, 0, 1, 2, 5, 0, 3, 0, 0}
    }};

    solver sudokuSolver(unsolvableRow);
    if(sudokuSolver.solveSudoku()) {
        sudokuSolver.printBoard();
        ASSERT_FALSE(true) << "This board should be unsolvable";
    }
}

// From 'Unsolvable Box', the center 3x3 square should be unsolvable
TEST(unsolvable, unsolvableBox){
    gameBoard unsolvableBox = {{
        {0, 9, 0, 3, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 8, 0, 0, 4, 6},
        {0, 0, 0, 0, 0, 0, 8, 0, 0},
        {4, 0, 5, 0, 6, 0, 0, 3, 0},
        {0, 0, 3, 2, 7, 5, 6, 0, 0},
        {0, 6, 0, 0, 1, 0, 9, 0, 4},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {5, 8, 0, 0, 2, 0, 0, 0, 0},
        {2, 0, 0, 0, 0, 7, 0, 6, 0}
    }};

    solver sudokuSolver(unsolvableBox);
    if(sudokuSolver.solveSudoku()) {
        sudokuSolver.printBoard();
        ASSERT_FALSE(true) << "This board should be unsolvable";
    }
}

// From 'Unsolvable Box', the column 5 should be unsolvable
// I'm going to leave this one disabled. It takes a while
// [       OK ] unsolvable.unsolvableColumn (381641 ms)
TEST(DISABLED_unsolvable, unsolvableColumn){
    gameBoard unsolvableColumn = {{
        {0, 0, 0, 0, 4, 1, 0, 0, 0},
        {0, 6, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0},
        {3, 2, 0, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 5, 0, 0, 4, 1},
        {7, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 2, 3, 0},
        {0, 4, 8, 0, 0, 0, 0, 0, 0},
        {5, 0, 1, 0, 0, 2, 0, 0, 0}
    }};

    solver sudokuSolver(unsolvableColumn);
    if(sudokuSolver.solveSudoku()) {
        sudokuSolver.printBoard();
        ASSERT_FALSE(true) << "This board should be unsolvable";
    }
}