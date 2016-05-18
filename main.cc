#include <fstream>
#include <iostream>
#include "board.h"
#include "solver.h"

const std::string SEPARATOR = "=========";

void solveSudoku(Solver solver, std::string sudokuString){
	std::cout << "Solving..." << std::endl;
	std::unique_ptr<Board> b = std::unique_ptr<Board>(new Board());

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	if(b->readBoardFromString(sudokuString)){
		b->printBoard();
		b = solver.solve(std::move(b));
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration<float, std::chrono::milliseconds::period>(end - begin).count();
		std::cout << "Solved in " << duration<< " milliseconds" << std::endl;
		b->printBoard();
	}
	else{
		std::cout << "Invalid Sudoku" << std::endl;
	}

	}

void solveAllInFile(std::string filename){
	int lineCount = 0;
	Solver solver;
	std::ifstream inFile;
	std::string line;
	std::string sudoku;

	inFile.open(filename);

	if(inFile.is_open()){
		std::cout << "Solving all sudokus in file " << filename << std::endl;
		while(getline(inFile, line)){
			if(line != SEPARATOR){
				sudoku += line;
				lineCount++;
				if(lineCount == 9){
					solveSudoku(solver, sudoku);
					lineCount = 0;
					sudoku.clear();
				}
			}
		}
		inFile.close();
	}
	else{
		std::cout << "Could not open file " << filename << std::endl;
	}	
}

int main(){
	solveAllInFile("sudoku.txt");
	return 0;
}