#include "solver.h"

/*
 *	Recursivly tries to solve the sudoku by trying to assign all possible
 *	values to the most constrained cell.
 */
std::unique_ptr<Board> Solver::solve(std::unique_ptr<Board> board){
	if(board == nullptr){
		// No solution found
		return board;
	}
	if(board->isSolved()){
		return board;
	}

	Cell* c = board -> getMostConstrainedCell();
	for(int i : c -> getPossibleValues()){
		// Try to assign each possible value to the most constrained cell
		std::unique_ptr<Board> b(new Board(*board));
		if(b->assign(b->getCell(c->getRow(), c->getCol()), i)){
			// Recursivly solve all boards where a possible value was 
			// successfully assigned
			if(std::unique_ptr<Board> newBoard = solve(std::move(b))){
				return newBoard;
			}
		}
	}
	// No solution found
	return nullptr;
}