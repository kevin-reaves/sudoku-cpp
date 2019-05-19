#include "sudoku.hpp"
#include <iostream>
#include <set>
#include <assert.h>
#include <bits/stdc++.h>


gridLayout solver::returnArray(){
    return grid;
}

gridLayout solver::generateBoard() {
    // This generate method could be better
    // Mostly getting something on paper so I can focus on testing
    int shuffleArray[N];
    for(int row=0; row<N; row++){
        shuffleArray[row] = row;
    }

    // Need to figure random seeds out later, don't want to keep putting time into it
    unsigned seed = 10000;
    shuffle(shuffleArray, shuffleArray + N-1, std::default_random_engine(seed));

    for(int row=0; row<N; row++){
        this->grid[0][row] = shuffleArray[row];
    }
    solveSudoku();

    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            if(row %2 == 0 && col % 2 == 0){
                this->grid[row][col] = 0;
            }
        }
    }
}

solver::solver(){
    for(int row = 0; row < N; row++){
        for(int col = 0; col < N; col++){
            this->grid[row][col] = 0;
        }
    }
    std::srand(time(nullptr));
    generateBoard();
}

solver::solver(gridLayout localGrid)
{
    for(int row = 0; row < localGrid.size(); row++){
        for(int col = 0; col < localGrid.size(); col++){
            this->grid[row][col] = localGrid[row][col];
        }
    }

    // confirm the input grid is valid
    assert (checkValid() == 1);
}

bool solver::solveSudoku()
{
    int row, col;
    if (!findUnassignedLocation(row, col))
        return true; // success

    for (int num = 1; num <= N; num++)
    {
        if (isSafe(row, col, num))
        {
            this->grid[row][col] = num;

            if (solveSudoku())
                return true; // success

            this->grid[row][col] = UNASSIGNED;
        }
    }
    return false; // backtracking
}

bool solver::findUnassignedLocation(int & row, int & col){
    for(row = 0; row < N; row++){
        for(col = 0; col < N; col++){
            if(this->grid[row][col] == UNASSIGNED){
                return true;
            }
        }
    }
    return false;
}

bool solver::usedInRow(int row, int num){
    for(int col = 0; col < N; col++){
        if(this->grid[row][col] == num){
            return true;
        }
    }
    return false;
}

bool solver::usedInCol(int col, int num){
    for(int row = 0; row < N; row++){
        if(this->grid[row][col] == num){
            return true;
        }
    }
    return false;
}

bool solver::usedInBox(int startBoxRow, int startBoxCol, int num){
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (this->grid[row+startBoxRow][col+startBoxCol] == num)
                return true;
    return false;
}

bool solver::isSafe(int row, int col, int num){
    return
        !usedInRow(row, num) &&
        !usedInCol(col, num) &&
        !usedInBox((row - row%3), (col - col % 3), num);
}

void solver::printGrid(){
    for (auto& row : this->grid)
    {
        for (auto& col : row)
        {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


bool solver::validRow(int row)
{
    std::set<int> used;

    for (int i = 0; i < N; i++) {
        if (used.find(this->grid[row][i]) != used.end())
            return false;

        if (this->grid[row][i] != 0)
            used.insert(this->grid[row][i]);
    }
    return true;
}

bool solver::validCol(int col)
{
    std::set<int> used;

    for (int i = 0; i < N; i++) {
        if (used.find(this->grid[i][col]) != used.end()) {
            return false;
        }

        if (this->grid[i][col] != 0)
            used.insert(this->grid[i][col]);
    }
    return true;
}

bool solver::validBox(int startBoxRow, int startBoxCol)
{
    std::set<int> used;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            int curr = this->grid[row + startBoxRow][col + startBoxCol];

            if (used.find(curr) != used.end() && curr != 0){
                return false;
            }

            if (curr != 0)
                used.insert(curr);
        }
    }
    return true;
}


bool solver::isValid(int row, int col)
{
    return  validRow(row) &&
            validCol(col) &&
            validBox(row - row % 3, col - col % 3);
}

bool solver::checkValid()
{
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            if (isValid(i, j) == 0) {
                return false;
            }
        }
    }
    return true;
}