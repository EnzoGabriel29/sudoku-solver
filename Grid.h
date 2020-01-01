#ifndef GRID_H
#define GRID_H

class Grid {
    public:
        Grid(int[9][9]);
        Grid getCopy();
        bool isEmpty(int, int);
        void setValue(int, int, int);

        void getGrid(int[9][9]);
        int getValue(int, int);
        void getRow(int[], int);
        void getColumn(int[], int);
        void get3x3Grid(int[], int, int);

    protected:
        int grid[9][9];
};

#endif
