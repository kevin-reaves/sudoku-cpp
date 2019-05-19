C++ Sudoku Solver - Backtracking Algorithm

* Clone google test before building
* https://github.com/google/googletest


<pre>
+-----+-----+-----+
|5 1 3|6 8 7|2 4 9|
|8 4 9|5 2 1|6 3 7|
|2 6 7|3 4 9|5 8 1|
+-----+-----+-----+
|1 5 8|4 6 3|9 7 2|
|9 7 4|2 1 8|3 6 5|
|3 2 6|7 9 5|4 1 8|
+-----+-----+-----+
|7 8 2|9 3 4|1 5 6|
|6 3 5|1 7 2|8 9 4|
|4 9 1|8 5 6|7 2 3|
+-----+-----+-----+
</pre>

## Rules

Zeroes are empty spaces on the board
No row, column, or 3x3 box can have the same number (1-9)

## Backtracking Algorithm

Confirm that the sudoku board to be solved is valid

Find row, col of an unassigned (0) cell

If there are none, return true

For digits 1-9 (for a 9x9 grid)

1. If there is no conflict (row/col/box duplicate number) at grid[row][col], assign a digit to the empty space

2. Recursively try to fill the rest of the grid in this way

3. If recursion is successful, return true

4. Else, remove the digit and try another

If all digits have been tried, there has been a problem. Return false