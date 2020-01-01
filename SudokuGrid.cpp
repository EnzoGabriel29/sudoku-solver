#include "SudokuGrid.h"
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>

const int SudokuGrid::DIGITS[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

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

bool SudokuGrid::checkDigits(int line[]){
    int auxLine[9];
    std::copy(line, line+9, auxLine);
    std::sort(auxLine, auxLine+9);

    for (int i = 0; i < 9; i++)
        if (auxLine[i] != DIGITS[i])
            return false;

    return true;
}

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
