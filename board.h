/*
* Author: Oscar Silver
*
* Filename: board.h
* Description: Represents a Sudoku board.
* Also provides logic to check if the board is solved.
*
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <cmath>
#include <string>
#include <vector>
#include "cell.h"

class Board{
private:
	int _size;
	int _squareSize;
	std::vector<Cell> _cells;

	bool isRowSolved(int);
 	bool isColSolved(int);
 	bool isSquareSolved();
public:
	Board() : _size(9), _squareSize(3), _cells(_size*_size, Cell(_size)){}
	Board(int size) : _size(size), _cells(_size*_size, Cell(_size)){
		_squareSize = sqrt(_size);
	}
	Cell* getCell(int, int);
	std::vector<Cell> getCells() const;
	int getSize() const;
	int getSquareSize() const;

	bool isSolved();

	void setEmptyBoard();
	void readBoardFromString(std::string);
	void printBoard();
};


#endif