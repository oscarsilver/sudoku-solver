#include "solver.h"

std::unique_ptr<Board> Solver::solve(std::unique_ptr<Board> board){
	if(board == nullptr){
		// No solution found
		return board;
	}
	if(board->isSolved()){
		return board;
	}

	Cell* nextCell = board -> getMostConstrainedCell();
	for(int possibleValue : nextCell -> getPossibleValues()){
		// Try to assign each possible value to the most constrained cell
		std::unique_ptr<Board> copyBoard(new Board(*board));
		if(copyBoard->assign(copyBoard->getCell(nextCell->getRow(), nextCell->getCol()), possibleValue)){
			// Recursivly solve all boards where a possible value was 
			// successfully assigned
			if((copyBoard = solve(std::move(copyBoard)))){
				return copyBoard;
			}
		}
	}
	// No solution found
	return nullptr;
}