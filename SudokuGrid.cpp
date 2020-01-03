#include "SudokuGrid.h"
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

const int SudokuGrid::DIGITS[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

/**
 *  Initializes a sudoku board.
 *  Upon receiving the board, the constructor also saves the last empty
 *  square of the board, where it starts with the last row and last column
 *  and scrolls from right to left and bottom to up until it finds an empty
 *  square. A sudoku board is solved only when this box is filled.
 *
 *  @param g an object representing a board (a Grid or a int[9][9])
 */
SudokuGrid::SudokuGrid(Grid g)
: grid(g){
    for (int i = 8; i >= 0; i--){
        for (int j = 8; j >= 0; j--){
            if (grid.isEmpty(i, j)){
                lastRow = i;
                lastColumn = j;
                return;
            }
        }
    }
}

/**
 *  Shows the formatted Sudoku board on the screen.
 */
void SudokuGrid::show(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (!i){
                if (!j) std::cout << "╔═══";
                else if (j % 3) std::cout << "╤═══";
                else std::cout << "╦═══";

            } else if (i % 3){
                if (!j) std::cout << "╟───";
                else if (j % 3) std::cout << "┼───";
                else std::cout << "╫───";

            } else {
                if (!j) std::cout << "╠═══";
                else if (j % 3) std::cout << "╪═══";
                else std::cout << "╬═══";
            }
        }

        if (!i) std::cout << "╗" << std::endl;
        else if (i % 3) std::cout << "╢" << std::endl;
        else std::cout << "╣" << std::endl;

        for (int j = 0; j < 9; j++){
            std::cout << (j % 3 ? "│ " : "║ ");

            if (grid.getValue(i, j))
                std::cout << grid.getValue(i, j) << " ";

            else std::cout << "  ";

        }

        std::cout << "║" << std::endl;
    }

    for (int j = 0; j < 9; j++){
        if (!j) std::cout << "╚═══";
        else if (j % 3) std::cout << "╧═══";
        else std::cout << "╩═══";
    }

    std::cout << "╝" << std::endl;
}

/**
 *  Solve the Sudoku board. The algorithm used is: for each square on the board,
 *  check if it is empty or not. If it's not empty, it moves to the next square
 *  from left to right and top to bottom. If it's empty, check the possible solutions
 *  for this square by analyzing the row, column and a 3x3 square belonging to
 *  this square. If there is only one solution, this square is filled with that
 *  solution and it moves to the next square. Otherwise, for each solution found,
 *  a new board is created with the same squares as the current one, the square
 *  corresponding to that position is filled with a possible solution and the
 *  algorithm is applied again to the new board. If the algorithm can solve the
 *  new board, the new board is returned. Otherwise, another possible solution is
 *  tested. If none of the possible solutions work, it's impossible to solve the board.
 *  If the board can be resolved, the attribute 'grid' is changed with the solution.
 *
 *  @returns 1 if the board can be solved else 0.
 */
bool SudokuGrid::solve(){
    int contSolutions;
    bool sols[9];

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (grid.isEmpty(i, j)){
                contSolutions = 0;
                for (int s = 0; s < 9; s++)
                    sols[s] = true;

                checkSolutions(sols, i, j);

                for (int s = 0; s < 9; s++)
                    if (sols[s]) ++contSolutions;

                if (!contSolutions)
                    return false;

                if (contSolutions == 1){
                    for (int s = 0; s < 9; s++){
                        if (sols[s]){
                            grid.setValue(i, j, s+1);
                            if (i == lastRow && j == lastColumn)
                                return true;
                            break;
                        }
                    }

                    continue;
                }

                for (int s = 0; s < 9; s++){
                    if (sols[s]){
                        Grid newGrid = grid.getCopy();
                        newGrid.setValue(i, j, s+1);

                        SudokuGrid sg = SudokuGrid(newGrid);

                        if (sg.solve()){
                            grid = sg.grid.getCopy();
                            return true;
                        }
                    }
                }

                return false;
            }
        }
    }

    return isSolved();
}

/**
 *  Checks for any given square the possible numbers that square can assume,
 *  taking into account the squares in the same row, column and 3x3 square.
 *
 *  @param sols an array of booleans with 9 positions, used as output. An array
 *              value of true means that the index of this value plus 1 is a
 *              possible solution to the square. The array to be passed as 
 *              parameter must have all elements set to true
 *  @param r the row of the square in the board
 *  @param c the column of the square in the board
 */
void SudokuGrid::checkSolutions(bool sols[], int r, int c){
    int pos;
    for (int i = 0; i < 9; i++){
        if (!grid.isEmpty(r, i)){
            pos = grid.getValue(r, i) - 1;
            sols[pos] = false;
        }

        if (!grid.isEmpty(i, c)){
            pos = grid.getValue(i, c) - 1;
            sols[pos] = false;
        }
    }

    int rul = r / 3;
    int cul = c / 3;

    for (int i = 3*rul; i < 3*rul+3; i++){
        for (int j = 3*cul; j < 3*cul+3; j++){
            if (!grid.isEmpty(i, j)){
                pos = grid.getValue(i, j) - 1;
                sols[pos] = false;
            }
        }
    }
}

/**
 *  Checks whether a vector contains values from 1 to 9, without
 *  repetitions. Useful for checking if a board row conforms to the rules.
 *  
 *  @param line array with 9 positions to be analyzed
 *  @returns if the vector, when sorted, equals to the values from 1 to 9
 */
bool SudokuGrid::checkDigits(int line[]){
    int auxLine[9];
    std::copy(line, line+9, auxLine);
    std::sort(auxLine, auxLine+9);

    for (int i = 0; i < 9; i++)
        if (auxLine[i] != DIGITS[i])
            return false;

    return true;
}

/**
 *  Checks if a Sudoku board is solved according to the Sudoku rules.
 *
 *  @returns if the board follows the Sudoku rules
 */
bool SudokuGrid::isSolved(){
    int auxLine[9];

    for (int i = 0; i < 9; i++){
        grid.getRow(auxLine, i);
        if (!checkDigits(auxLine)) return false;
    }

    for (int i = 0; i < 9; i++){
        grid.getColumn(auxLine, i);
        if (!checkDigits(auxLine)) return false;
    }

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            grid.get3x3Grid(auxLine, i, j);
            if (!checkDigits(auxLine)) return false;
        }
    }

    return true;
}
