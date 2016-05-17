#include "solver.h"
#include <iostream>

std::unique_ptr<Board> Solver::solve(std::unique_ptr<Board> board){
	if(board == nullptr){
		return board;
	}
	if(board->isSolved()){
		return board;
	}
	Cell* c = board -> getMostConstrainedCell();
	for(int i : c ->getPossibleValues()){
		std::unique_ptr<Board> b(new Board(*board));
		if(b->assign(b->getCell(c->getRow(), c->getCol()), i)){
			if(std::unique_ptr<Board> newBoard = solve(std::move(b))){
				return newBoard;
			}
		}
	}
	return nullptr;
}