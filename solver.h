/*
* Author: Oscar Silver
* Filename: solver.h
* Description: 
* Takes a sudoku board and tries to solve it recursivly.
* Returns true is the board was succesfully solved and false if no solution was found.
* 
*/
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include <vector>
#include <queue>
#include "board.h"

class Solver{
public:
	/*
 	 *	Tries to solve the sudoku recursivly by trying to assign all possible
 	 *	values to the most constrained cell.
 	 */
	bool solve(Board&);
};


#endif