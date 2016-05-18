#include "solver.h"

bool Solver::solve(Board& board){
	if(board.isSolved()){
		return true;
	}

	Cell* nextCell = board.getMostConstrainedCell();
	for(int possibleValue : nextCell -> getPossibleValues()){
		// Try to assign each possible value to the most constrained cell
		Board copyBoard(board);
		if(copyBoard.assign(copyBoard.getCell(nextCell->getRow(), nextCell->getCol()), possibleValue)){
			// Recursivly solve all boards where a possible value was 
			// successfully assigned
			if(solve(copyBoard)){
				board = copyBoard;
				return true;
			}
		}
	}
	// No solution found
	return false;
}