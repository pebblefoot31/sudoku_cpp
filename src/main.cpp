#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

int main(int argc, char* argv[]) {

    //read in a file as a commandline argument so that i can easily take in different puzzles 
    char* file;
    std::string fileName;

    //error check cmdline args: ensure correct amount and type (the file must end in 'txt')
    if (argc != 2) {
        std::cerr << "Incorrect num of args." << std::endl;
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

    std::vector<std::vector<int>> sudokuPuzzle(9);

    std::string line;
    //char num;
    int count = 0;
    int row = 0;

    //use getline and stringstream to populate the vector buffer + output puzzle
    std::cout << "============================" << std::endl;
    std::cout << "        THE PUZZLE" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "Row " << row + 1 << ":     "; 
    while (getline(inputFile, line)) {

        std::stringstream numbers(line);
        std::string numString;
        
        while (numbers >> numString) {

            if (count == 9) {
                row++;
                std::cout << std::endl;
                std::cout << "Row " << row + 1 << ":     "; 
                count = 0;
            }

            if (numString == "-") {
                sudokuPuzzle[row].push_back(0);
                std::cout << "0 "; 
            }

            else {
                int num = atoi(numString.c_str());
                sudokuPuzzle[row].push_back(num);
                std::cout << num << " "; 
            }

            count++;
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;

    int col = 0;
    int colLimit = 0;
    count = 0;

    /*
    std::cout << "verifying buffer. " << std::endl;
    std::cout << std::endl;
    


    for (row = 0; row < 9; row++){

        for (col = 0; col < 9; col++) {

            std::cout << sudokuPuzzle[row][col] << " "; 
        }

        std::cout << std::endl;
    }*/

    int rowcount;
    std::cout << "3x3 GRID:" << std::endl;
    vector<int> numbers = {1,2,3,4,5,6,7,8,9};
    vector<pair<int, int>> coordinates;

    while (true) {
        
        //iterating through 3x3 grids
        for (row = 0; row < 9; row++) {


            //printing 3 column values per row
            while (count < 3) {

                if (sudokuPuzzle[row][col] == 0) {
                    coordinates.push_back(make_pair(row, col));
                    std::cout << "Empty value. Adding coordinate pair to vector of empty box coordinates." << std::endl;
                }

                std::cout << sudokuPuzzle[row][col] << " "; 

                if (count == 2) {
                    //std::cout << std::endl;
                    std::cout << std::endl;
                }


                col++;
                count++;
            }

            count = 0;
            col = colLimit;
            
            if ((row+1)%3 == 0){ 
                std::cout << std::endl;
                std::cout << "3x3 GRID:"; 
                std::cout << std::endl;

                //if the empty coordinates vector ISNT empty after first traversal... 
                //do not update finished grid count
                //traverse the grid AGAIN, this time going to every coordinate in coordinates vector
                //try all values 1-9 in each coordinate in the empty list
                //use validate functions to see if it fits
                //if works, pop that coordinate from that vector, move on to next pair in vector
                //after having gone through entire vector and trying nums in 
                //clear the vector. 
                //
                //if it IS empty.....
                //move on to next grid and repeat begin first traversal
                //update finished_grid count by 1
            }
        }

        if (col < 5) {
            
            colLimit +=3;
            col = colLimit;
            row = 0;
        }

        else {

            break;
        }
    }


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

