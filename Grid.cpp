#include "Grid.h"

Grid::Grid(int g[9][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            grid[i][j] = g[i][j];
}

Grid Grid::getCopy(){
    int newGrid[9][9];
    getGrid(newGrid);
    return Grid(newGrid);
}

bool Grid::isEmpty(int r, int c){
    return grid[r][c] == 0;
}

void Grid::setValue(int r, int c, int v){
    grid[r][c] = v;
}

int Grid::getValue(int r, int c){
    return grid[r][c];
}

void Grid::getRow(int row[], int r){
    for (int c = 0; c < 9; c++)
        row[c] = grid[r][c];
}

void Grid::getColumn(int column[], int c){
    for (int r = 0; r < 9; r++)
        column[c] = grid[r][c];
}

void Grid::get3x3Grid(int grid3x3[], int i, int j){
    i *= 3;
    j *= 3;

    for (int r = i; r < 3; r++)
        for (int c = j; c < 3; c++)
            grid3x3[3*i+j] = grid[r+i][c+j];
}

void Grid::getGrid(int newGrid[9][9]){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            newGrid[i][j] = grid[i][j];
}
