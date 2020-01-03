# Sudoku solver

A sudoku solver using only brute-force and little else.

## How to use

Using the Terminal, clone the repository:

    git clone https://github.com/EnzoGabriel29/sudoku-solver

Change the directory to `sudoku-solver` folder and compile the source:

    g++ -o main main.cpp Grid.cpp SudokuGrid.cpp

Save a file with values separated by space representing a Sudoku board
(file examples are in the folder `sudoku-examples` of the project). After 
that, run the executable with the name of the file:

    ./main sudoku-examples/grid3.txt

The output of the above command is:

![](https://i.imgur.com/wje9iH3.png)