#include "Grid.h"

/**
 *  Initializes a board. This class aims to facilitate some operations performed
 *  on the board, such as obtaining a copy of the board or turning a 3x3 square
 *  into a array of 9 positions.
 *  
 *  @param g a 3x3 matrix representing a board
 */
Grid::Grid(int g[9][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j] = g[i][j];
}

/**
 *  Produces a copy of the current board. Useful when you want to perform more
 *  scenarios to verify if a solution is valid.
 *
 *  @returns a copy of the current grid
 */
Grid Grid::getCopy(){
    int newGrid[9][9];
    getGrid(newGrid);
    return Grid(newGrid);
}

/**
 *  Checks if a square on the board is empty.
 *
 *  @param r the row of the square
 *  @param c the column of the square
 *  @returns if the square is empty
 */
bool Grid::isEmpty(int r, int c){
    return grid[r][c] == 0;
}

/**
 *  Sets a value for a square on the board.
 *
 *  @param r the row of the square
 *  @param c the column of the square
 *  @param v the new value of the square
 */
void Grid::setValue(int r, int c, int v){
    grid[r][c] = v;
}

/**
 *  Returns the value of a square on the board.
 *
 *  @param r the row of the square
 *  @param c the column of the square
 *  @returns the value of the square
 */
int Grid::getValue(int r, int c){
    return grid[r][c];
}

/**
 *  Copy a row from the board into a array.
 *
 *  @param row the array to be copied to
 *  @param r the row to be copied
 */
void Grid::getRow(int row[], int r){
    for (int c = 0; c < 9; c++)
        row[c] = grid[r][c];
}

/**
 *  Copy a column from the board into a array.
 *
 *  @param column the array to be copied to
 *  @param c the row to be copied
 */
void Grid::getColumn(int column[], int c){
    for (int r = 0; r < 9; r++)
        column[c] = grid[r][c];
}

/**
 *  Copy a 3x3 square from the board into a array.
 *
 *  @param grid3x3 the array to be copied to
 *  @param i horizontal index of a 3x3 square on the board
 *  @param j vertical index of a 3x3 square on the board
 */
void Grid::get3x3Grid(int grid3x3[], int i, int j){
    i *= 3;
    j *= 3;

    for (int r = i; r < 3; r++)
        for (int c = j; c < 3; c++)
            grid3x3[3*i+j] = grid[r+i][c+j];
}

/**
 *  Copy the current board into a 9x9 matrix.
 *
 *  @param newGrid the matrix to be copied to
 */
void Grid::getGrid(int newGrid[9][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            newGrid[i][j] = grid[i][j];
}
