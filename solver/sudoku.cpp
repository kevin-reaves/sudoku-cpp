#include "sudoku.hpp"
#include <iostream>
#include <set>
#include <bits/stdc++.h>
#include <algorithm>
#include <random>
#include <chrono>

gameBoard solver::returnBoard(){
    return this->board;
}


gameBoard solver::generateBoard() {

    long seed = std::chrono::system_clock().now().time_since_epoch().count();
    std::default_random_engine e(seed);

    int shuffleArray[BOARDSIZE];

    // Creates an array of 1..9
    for (int row = 0; row < BOARDSIZE; row++) {
        shuffleArray[row] = row;
    }

    // Randomizes the array
    shuffle(shuffleArray, shuffleArray + BOARDSIZE - 1, e);

    // Uses the random array to be the top row of this->board
    for (int row = 0; row < BOARDSIZE; row++) {
        this->board[0][row] = shuffleArray[row];
    }

    solveSudoku();

    // will revert roughly half of numbers back to 0 randomly
    int thanos;

    for (int row = 0; row < BOARDSIZE; row++) {
        for (int col = 0; col < BOARDSIZE; col++) {
            // 101 generates random numbers from 0..100
            thanos = rand() % 101;
            if (thanos < 50) {
                this->board[row][col] = 0;
            }
        }
    }
}


solver::solver() {
    for (int row = 0; row < BOARDSIZE; row++) {
        for (int col = 0; col < BOARDSIZE; col++) {
            this->board[row][col] = 0;
        }
    }

    generateBoard();
}

/*
 * TODO
 * Figure out how to do this without loading the whole board into
 * memory or creating a duplicate function call for isValidBoard.
 */
solver::solver(gameBoard localBoard) {
    for (int row = 0; row < localBoard.size(); row++) {
        for (int col = 0; col < localBoard.size(); col++) {
            this->board[row][col] = localBoard[row][col];
        }
    }

    // confirm the input board is valid
    if (!isValidBoard()){
        throw std::invalid_argument("The board you've passed into the constructor is invalid");
    }
}

bool solver::solveSudoku()
{
    int row = 0, col = 0;

    // If there are no more zeroes on the board, it's (almost certainly) solved
    if (!findUnassignedLocation(row, col)) {
        if(isValidBoard()){
            return true; // success
        } else {
            throw std::runtime_error("An invalid board has made it through the solver");
        }
    }

    // Backtracking algorithm
    // Try placing a number, then follow that path until you either
    // solve the board or decide that was not the correct path
    // If that was not the correct path, back up and try another number
    for (int num = 1; num <= BOARDSIZE; num++)
    {
        this->board[row][col] = num;

        if (isValidMove(row, col))
        {
            if (solveSudoku())
            {
                return true; // success
            }
            else
            {
                // The move doesn't lead towards a path that solves the puzzle, it needs to be backed out
                this->board[row][col] = UNASSIGNED;
            }
        }
        else
        {
            // The move isn't valid, it needs to be backed out
            this->board[row][col] = UNASSIGNED;
        }
    }
    return false; // backtracking
}

// This function modifies the arguments passed into it
bool solver::findUnassignedLocation(int & row, int & col){
    for(row = 0; row < BOARDSIZE; row++){
        for(col = 0; col < BOARDSIZE; col++){
            if(this->board[row][col] == UNASSIGNED){
                return true;
            }
        }
    }
    // There are no more zeroes on the board
    return false;
}

const void solver::printBoard() {
    for (auto &row : this->board) {
        for (auto &col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Checks to make sure a row doesn't contain any duplicate numbers
const bool solver::isValidRow(const int row) {
    std::set<int> used;

    for (int i = 0; i < BOARDSIZE; i++) {
        if (used.find(this->board[row][i]) != used.end())
            return false;

        if (this->board[row][i] != 0)
            used.insert(this->board[row][i]);
    }
    return true;
}

// Checks to make sure a column doesn't contain any duplicate numbers
const bool solver::isValidCol(const int col) {
    std::set<int> used;

    for (int i = 0; i < BOARDSIZE; i++) {
        if (used.find(this->board[i][col]) != used.end()) {
            return false;
        }

        if (this->board[i][col] != 0)
            used.insert(this->board[i][col]);
    }
    return true;
}

// Checks to make sure a box (3x3 square) doesn't contain any duplicate values
// Also checks to make sure none of the values in the box are outside 0-9
const bool solver::isValidBox(const int startRow, const int startCol) {
    std::set<int> used;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int curr = this->board[row + startRow][col + startCol];

            // Curr has been used before      ||  curr is too big  || curr is too small
            if (used.find(curr) != used.end() || (curr > BOARDSIZE || curr < 0)) {
                return false;
            }

            if (curr != 0)
                used.insert(curr);
        }
    }
    return true;
}

// Calls the functions to check row, column, and box safety for a given board space
const bool solver::isValidMove(const int row, const int col) {
    return isValidRow(row) &&
           isValidCol(col) &&
           isValidBox(row - row % 3, col - col % 3);
}

// Calls the functions to check row, column, and box safety for the whole board
const bool solver::isValidBoard() {
    // Keeping up with the counters for row/col and 3x3 grid
    for (int colRow = 0, grid = 0; colRow < BOARDSIZE; colRow++, grid++) {
        // returns false if any of the rows or columns are invalid
        if (!isValidRow(colRow) || !isValidCol(colRow)) {
            return false;
        }
        if (grid % 3 == 0) {
            // returns false if any of the grids are invalid
            // only need to run the grid checker every three iterations
            if (!isValidBox(colRow, grid)) {
                return false;
            }
        }
    }
    return true;
}