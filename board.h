/*
* Author: Oscar Silver
*
* Filename: board.h
*
* Description: 
* Represents a Sudokuboard. Responsible for checking that assignment of values
* to its cells are valid.
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include "cell.h"

class Board{
private:
	int _size;
	int _squareSize;
	std::vector<Cell> _cells;

	bool eliminateRow(int, int, int);
	bool eliminateCol(int, int, int);
	bool eliminateSquare(int, int, int);
	void initBoard();
public:
	Board() : _size(9), _squareSize(3), _cells(_size*_size, Cell(_size)){}
	~Board() = default;
	Board(const Board&) = default;
	Board& operator=(Board& other) = delete;
	Board(Board&&) = delete;
	Board&& operator=(Board&& other) = delete;

	Cell* getCell(int, int);
	Cell* getMostConstrainedCell();
	int getSize() const;
	int getSquareSize() const;

	bool isSolved() const;
	bool assign(Cell*, int);
	bool eliminate(Cell*, int);

	bool readBoardFromString(std::string);
	void printBoard();
};

#endif