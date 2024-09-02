#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>

//SUDOKU SOLVER

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

bool check_val(int row, int col, int value, std::vector<int> &gridVals, std::vector<std::vector<int>> &puzzle) {

    for (int i = 0; i < 9; i++) {
        if (puzzle[row][i] == value)
            return false; //invalid in the row
    }

    for (int j = 0; j < 9; j++) {
        if (puzzle[j][col] == value)
            return false; //invalid in the column
    }

    for (size_t k = 0; k < gridVals.size(); k++) {
        if (gridVals[k] == value)
            return false; //invalid in the grid 
    }

    return true;
}

bool check_solved(std::vector<std::vector<int>> &puzzle) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[i][j] == 0)
                return false;
        }
    }

    return true;
}

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

    //declaring puzzle matrix
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
    bool solved = false;

    /*
    std::cout << "verifying buffer. " << std::endl;
    std::cout << std::endl;

    for (row = 0; row < 9; row++){
        for (col = 0; col < 9; col++)
            std::cout << sudokuPuzzle[row][col] << " "; 
        std::cout << std::endl;
    }*/

    int rowcount;
    std::vector<int> grid;  //maintaining a list of values present in current 3x3 grid 
    std::vector<std::pair<int, int>> coordinates; //maintaining a list of coordinate pairs 
                                        //that have 0 (represent empty boxes) in current 3x3 grid

    //solving the puzzle each 3x3 grid at a time
    while (!solved) {
        
        if (check_solved(sudokuPuzzle)) {
            solved = true;
            break;
        }

        //iterating through grids row by row
        for (row = 0; row < 9; row++) {

            //printing 3 column values per row
            while (count < 3) {

                //checking for empty value. Adding coordinate pair to vector 
                //of empty box coordinates for this particular grid
                if (sudokuPuzzle[row][col] == 0)
                    coordinates.push_back(std::make_pair(row, col));
                else
                    grid.push_back(sudokuPuzzle[row][col]);


                //std::cout << sudokuPuzzle[row][col] << " "; 

                //done printing 3 vals for that row
                /*if (count == 2)
                    std::cout << std::endl;*/

                //updating column and how many vals have been printed in the row
                col++;
                count++;
            } 

            
            count = 0; //re-starting set of 3 for next row
            col = colLimit; 
            
            if ((row+1)%3 == 0) { 

                //std::cout << std::endl;

               //if the grid had at least one empty box
               if (!coordinates.empty()) { 

                    //iterating through the list of empty boxes
                    for (size_t v = 0; v < coordinates.size(); v++) {

                        //attempting every value 1-9 in empty box
                        for (int n = 1; n < 10; n++) { 

                            //checking to make sure that the grid isn't full
                            if (coordinates.empty()) {
                                break;
                            }

                            //checking if the the value works. if it does, assigning in actual puzzle.
                            if (check_val(coordinates[v].first, coordinates[v].second, n, grid, sudokuPuzzle)) {

                                sudokuPuzzle[coordinates[v].first][coordinates[v].second] = n;

                                //erasing that coordinate pair from the coordinates vector 
                                if (v < coordinates.size()) {

                                    //Convert index to iterator
                                    std::vector<std::pair<int,int>>::iterator it = coordinates.begin() + v;

                                    //Erasing the element at the iterator position
                                    coordinates.erase(it);
                                } 
                                else {
                                    std::cout << "Index out of bounds." << std::endl;
                                }

                                //adding n (the number that worked) to present grid vals and moving onto next empty coordinate in the grid
                                grid.push_back(n);
                                break;
                            }
                        }
                    }

                    //resetting the grid and coordinates for next 3x3
                    grid.clear();
                    coordinates.clear();

                }

               //if all coordinates of this grid ARE full!
               else {

                    if (check_solved(sudokuPuzzle)) { //checking if the puzzle is solved
                        solved = true;
                        break;
                    }
               }

                //std::cout << "3x3 GRID:"; 
                //std::cout << std::endl;
            }
        }

        if (col < 5) {
            
            colLimit +=3; //moving to the right in terms of starting col coordinate 
            col = colLimit;
            row = 0; //starting from top row again
        }

        else {
            col = 0; //iterating through puzzle again from the beginning
        }

    }

    std::cout << "solved puzzle." << std::endl;

    inputFile.close();

    return 0;

}

