/*
* Author: Oscar Silver
* Filename: solver.h
* Description: Takes an unsolved Sudoku board and prints the solved board.
*
*/
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <vector>
#include <queue>
#include "board.h"

struct EmptyCellComparator{
	bool operator() (const Cell& lhs, const Cell& rhs){
		return lhs.getPossibleValueCount() < rhs.getPossibleValueCount();
	}
};

typedef std::priority_queue<Cell, std::vector<Cell>, EmptyCellComparator> empty_cell_queue;

class Solver{
	bool _solved;
public:
	Solver() : _solved(false){};
	bool solve(Board*);
};


#endif