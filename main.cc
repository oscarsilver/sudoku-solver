#include <fstream>
#include <iostream>
#include "board.h"
#include "solver.h"

void solveSudoku(Solver solver, std::string sodukoString, int size){
	Board* b = new Board(size);
	b->readBoardFromString(sodukoString);
	b->printBoard();
	solver.solve(b);
}

void solveAllInFile(std::string filename, int sudokuSize){
	int lineCount = 0;
	Solver solver;
	std::ifstream inFile;
	std::string line;
	std::string sudoku;

	inFile.open("Boards/" + filename);

	if(inFile.is_open()){
		std::cout << "Solving all sudokus in file " << filename << std::endl;
		while(getline(inFile, line)){
			sudoku += line;
			lineCount++;
			if(lineCount == sudokuSize){
				std::cout << "Solving: " << std::endl;
				solveSudoku(solver, sudoku, sudokuSize);
				lineCount = 0;
				sudoku.clear();
			}
		}
		inFile.close();
	}
	else{
		std::cout << "Could not open file " << filename << std::endl;
	}	
}

int main(){
	solveAllInFile("small-sudoku.txt", 9);
	return 0;
}