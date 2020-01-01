# Sudoku solver

A sudoku solver using only brute-force and a little else.

## How to use

Using the Terminal, clone the repository:

    git clone https://github.com/EnzoGabriel29/sudoku-solver

Open `main.cpp` file and, in the source code, there will be three two-dimensional vectors.
These vectors represent a Sudoku board (note that they are 9x9), where the missing squares
have the value 0. You can test the available boards or add your own. Line 40 of the file
defines which matrix will be used as a board. After defining a board to use, save the file
change the directory to `sudoku-solver` folder and compile the source:

    g++ -o main main.cpp Grid.cpp SudokuGrid.cpp

After that, run the executable:

    ./main

## TODO

- [ ] Add source code documentation

- [ ] Add a board via text file

- [ ] Some code improvements