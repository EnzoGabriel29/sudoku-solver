#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include "Grid.h"

class SudokuGrid {
    public:
        SudokuGrid(Grid);
        void show();
        bool solve();
        bool isSolved();
        void checkSolutions(bool[], int, int);

    protected:
        static const int DIGITS[];

        Grid grid;
        int lastRow, lastColumn;

        bool checkDigits(int[]);
};

#endif
