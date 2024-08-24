#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    //read in a file as a commandline argument so that i can easily take in different puzzles 
    char* file;
    std::string fileName;

    //error check cmdline args: ensure correct amount and type (the file must end in 'txt')
    if (argc != 2) {
        std::cerr << "Too many args." << std::endl;
        return 1;
    }

    //error checking file
    file = argv[(argc-1)];
    fileName = file; //converting char* file name into string

    if (fileName.substr(fileName.length() - 4) != ".txt") {
        std::cerr << "Invalid file type." << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[(argc-1)]);
    if (!inputFile) {
        std::cerr << "Unable to open file." << std::endl; 
        return 1;
    }

    std::vector<std::vector<int>> sudokuPuzzle(9, std::vector<int>(9,0));    //initializing a 9x9 matrix filled in with 0s

    std::string line;
    char num;
    int count = 0;
    int row = 0;

    //use getline and stringstream to populate the vector buffer + output puzzle
    /*std::cout << "============================" << std::endl;
    std::cout << "        THE PUZZLE" << std::endl;
    std::cout << "============================" << std::endl;*/
    std::cout << "Row " << row + 1 << ":     "; 
    while (getline(inputFile, line)) {

        std::stringstream numbers(line);
        while (numbers >> num) {

            if (count == 9) {
                row++;
                std::cout << std::endl;
                std::cout << "Row " << row + 1 << ":     "; 
                count = 0;
            }

            if (num == '-') {
                sudokuPuzzle[row].push_back(0);
                std::cout << "0 "; 
            }

            else {
                sudokuPuzzle[row].push_back(num);
                std::cout << num << " "; 
            }

            count++;
        }
    }
    std::cout << std::endl;

    //simplified algorithm for solving the 9x9 sudoku puzzle
    //1. validate current puzzle by traversing through each value in each 3x3 grid of 
    //   this puzzle from left to right or top to bottom (whichever is easier)
    //2. after having validated the original puzzle (i.e. checking that all rules of 
    //   sudoku have been met), beginning going throuhg each 3x3 grid and establish a 
    //   way to keep track of which spaces are empty (coordinate pair) and which number
    //   is missing from each the grid 
    //3. After collecting this information for that particular 3x3 grid, go through the
    //   list of empty spaces in that grid and try each missing value for that particular
    //   3x3 grid
    //4. 'Try each value': check it's compatibility in the context of the row you are looking at,
    //   the column, and the 3x3 grid.
    //5. If the 'try' is successful for a value, then apply 'validate' and double check 
    //   the placement? (this step may be redundant and unnecessary)
    //6. If you are able to place a value successfully into the grid, try all of the values 
    //   again in the remaining spaces in that grid (until you either run out of values 
    //   to try or none of the values working anymore.)
    //7. Loop through the entire puzzle or grid to check for 0s. If there are still 0s,
    //   move on to the next grid.
    //8. Repeat steps until the puzzle has no 0s remaining: this will be the solved puzzle.

    inputFile.close();

    return 0;

}

