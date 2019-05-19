#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <vector>
#include <array>
#define UNASSIGNED 0
#define N 9
using gridLayout = std::array<std::array<int, N>, N>;



class solver{
private:
    gridLayout grid;

    // Finds empty spots in the grid. Empty spots are zeroes
    bool findUnassignedLocation(int & row, int & col);
    // Checks to make sure a value hasn't been used in that row
    bool usedInRow(int col, int num);
    // Checks to make sure a value hasn't been used in that column
    bool usedInCol(int row, int num);
    // Checks to make sure a value hasn't been used in that box
    bool usedInBox(int startBoxRow, int startBoxCol, int num);
    // Wrapper method to check row/col/box
    bool isSafe(int row, int col, int num);

    // The below methods are checking the input grid to make sure it follows sudoku rules
    // Makes sure a row is valid
    bool validRow(int row);
    // Makes sure a column is valid
    bool validCol(int col);
    // Makes sure a box is valid
    bool validBox(int startBoxRow, int startBoxCol);
    // Wrapper method to check row/col/box
    bool isValid(int row, int col);
public:
    // Getter for testing purposes
    // Would like to make project more functional
    std::array<std::array<int, N>, N> returnArray();
    // Runner for the backtracking algorithm
    bool solveSudoku();
    // Runner for initial grid validation
    bool checkValid();
    // Runner for printing the grid
    void printGrid();
    // Constructor. Initializes and validates the grid
    explicit solver(gridLayout localGrid);

};
#endif //SUDOKU_HPP