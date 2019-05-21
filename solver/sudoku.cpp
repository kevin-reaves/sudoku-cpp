#include "sudoku.hpp"
#include <iostream>
#include <set>
#include <assert.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

gridLayout solver::returnArray(){
    return grid;
}

gridLayout solver::generateBoard() {

    unsigned seed = std::chrono::system_clock().now().time_since_epoch().count();
    std::default_random_engine e(seed);

    int shuffleArray[N];
    for(int row=0; row<N; row++){
        shuffleArray[row] = row;
    }

    shuffle(shuffleArray, shuffleArray + N-1, e);

    for(int row=0; row<N; row++){
        this->grid[0][row] = shuffleArray[row];
    }

    solveSudoku();

    // will revert some numbers back to 0 randomly
    int thanos;

    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            thanos = rand() % 101;
            if(thanos < 50){
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