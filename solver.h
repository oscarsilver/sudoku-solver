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
	empty_cell_queue _emptyCells;
	std::vector<Cell> _filledCells;
	bool _solved;

	Cell* getNextEmptyCell(Board* b);
	void clearEmptyCells();
	void separateEmptyCells(Board* b);
	bool onSolved(Board* b);
	bool isInSameSquare(int r1, int c1, int r2, int c2, int squareSize);
	void removePossibleValues(Cell* c, Board* b);
public:
	Solver() : _emptyCells(), _filledCells(0), _solved(false){};
	bool solve(Board*);
};


#endif