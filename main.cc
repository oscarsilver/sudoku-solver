#include <fstream>
#include <iostream>
#include "board.h"
#include "solver.h"

/*
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

*/
const std::string sampleBoard = "020810740700003100090002805009040087400208003160030200302700060005600008076051090";
const std::string testBoard = "200000000000000000000000000000000000000000000000000000000000000000000000000000093";
const std::string solvedBoard = "523816749784593126691472835239145687457268913168937254342789561915624378876351492";
const std::string harderBoard = "001900003900700160030005007050000009004302600200000070600100030042007006500006800";
const std::string evenHarderBoard = "043080250600000000000001094900004070000608000010200003820500000000000005034090710";

int main(){
	Board* board = new Board();
	board->readBoardFromString(evenHarderBoard);
	Solver solver;
	std::unique_ptr<Board> b = solver.solve(std::unique_ptr<Board>(board));
	b->printBoard();
	//std::cout << std::boolalpha << solver.solve(std::unique_ptr<Board>(board)) << std::endl;
	
	return 0;
}