#include "SudokuGrid.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()){
        std::cerr << "Error: " << "the file " << argv[1];
        std::cerr << " was not found" << std::endl;
        return 1;
    }

    int grid[9][9];

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            file >> grid[i][j];

    SudokuGrid sg(grid);

    sg.show();
    std::cout << std::endl;

    if (sg.solve()){
        sg.show();
    
    } else {
        std::cout << "The provided grid could not be solved." << std::endl;
    }
}