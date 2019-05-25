#include "sudoku.hpp"
#include <iostream>
#include <set>
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <random>
#include <chrono>

gameBoard solver::returnBoard(){
    return this->board;
}


gameBoard solver::generateBoard() {

    unsigned seed = std::chrono::system_clock().now().time_since_epoch().count();
    std::default_random_engine e(seed);

    int shuffleArray[BOARDSIZE];
    for (int row = 0; row < BOARDSIZE; row++) {
        shuffleArray[row] = row;
    }

    shuffle(shuffleArray, shuffleArray + BOARDSIZE - 1, e);

    for (int row = 0; row < BOARDSIZE; row++) {
        this->board[0][row] = shuffleArray[row];
    }

    solveSudoku();

    // will revert roughly half of numbers back to 0 randomly
    int thanos;

    for (int row = 0; row < BOARDSIZE; row++) {
        for (int col = 0; col < BOARDSIZE; col++) {
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

solver::solver(gameBoard localBoard) {
    /*
     * TODO
     * Figure out how to do this without loading the whole board into
     * memory or creating a duplicate function call for isValidBoard.
     * isValidBoard has lots of logic. May need to break it out
     */
    for (int row = 0; row < localBoard.size(); row++) {
        for (int col = 0; col < localBoard.size(); col++) {
            this->board[row][col] = localBoard[row][col];
        }
    }

    // confirm the input board is valid
    assert (isValidBoard());
}

bool solver::solveSudoku()
{
    int row = 0, col = 0;
    if (!findUnassignedLocation(row, col)) {
        return true; // success
    }

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

const bool solver::findUnassignedLocation(int & row, int & col){
    for(row = 0; row < BOARDSIZE; row++){
        for(col = 0; col < BOARDSIZE; col++){
            if(this->board[row][col] == UNASSIGNED){
                return true;
            }
        }
    }
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

const bool solver::isValidRow(int row) {
    std::set<int> used;

    for (int i = 0; i < BOARDSIZE; i++) {
        if (used.find(this->board[row][i]) != used.end())
            return false;

        if (this->board[row][i] != 0)
            used.insert(this->board[row][i]);
    }
    return true;
}

const bool solver::isValidCol(int col) {
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

const bool solver::isValidBox(int startRow, int startCol) {
    std::set<int> used;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int curr = this->board[row + startRow][col + startCol];

            if (used.find(curr) != used.end() && curr != 0) {
                return false;
            }

            if (curr != 0)
                used.insert(curr);
        }
    }
    return true;
}


const bool solver::isValidMove(int row, int col) {
    return isValidRow(row) &&
           isValidCol(col) &&
           isValidBox(row - row % 3, col - col % 3);
}

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