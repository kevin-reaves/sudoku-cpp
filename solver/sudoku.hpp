#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <array>

#define UNASSIGNED 0

// Size of a the sudoku board
// For example, a board size of 9 means a 9x9 board and 81 spaces total
#define BOARDSIZE 9

typedef std::array<std::array<int, BOARDSIZE>, BOARDSIZE> gameBoard;


class solver {
private:
    gameBoard board;

    // Finds empty spots (UNASSIGNED) in the board
    const bool findUnassignedLocation(int & row, int & col);

    // Checks if a row is valid
    const bool isValidRow(int row);

    // Checks if a column is valid
    const bool isValidCol(int col);

    // Checks if a box is valid
    const bool isValidBox(int startRow, int startCol);

    /*
     * Used for validating individual moves, use isValidBoard to validate the whole board
     * Calls the isValidRow, isValidCol, isValidBox methods
     */
    const bool isValidMove(int row, int col);

    // Generate random board, called by default constructor
    gameBoard generateBoard();

public:
    // Prints a gameBoard object to the console
    const void printBoard();

    // Checks to make sure the entire board is valid
    const bool isValidBoard();

    // Getter for testing purposes
    gameBoard returnBoard();

    // Runner for the backtracking algorithm
    bool solveSudoku();

    // Takes a board, checks to make sure it's valid
    explicit solver(gameBoard localBoard);

    // Default constructor. Returns a random board
    solver();

};

#endif //SUDOKU_HPP