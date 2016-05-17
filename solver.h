/*
* Author: Oscar Silver
* Filename: solver.h
* Description: Takes a pointer to an unsolved sudoku board and returns a solved board.
*/
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <vector>
#include <queue>
#include "board.h"

class Solver{
public:
	std::unique_ptr<Board> solve(std::unique_ptr<Board>);
};


#endif