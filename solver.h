/*
* Author: Oscar Silver
* Filename: solver.h
* Description: 
* Takes a sudoku board and tries to solve it recursivly.
* If a solution is found the solved board is returned. If no solution is found
* a nullptr is returned.
*/
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <vector>
#include <queue>
#include "board.h"

class Solver{
public:
	/*
 	 *	Recursivly tries to solve the sudoku by trying to assign all possible
 	 *	values to the most constrained cell.
 	 */
	std::unique_ptr<Board> solve(std::unique_ptr<Board>);
};


#endif