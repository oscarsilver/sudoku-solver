/*
* Author: Oscar Silver
*
* Filename: cell.h
* Description: Represents a Cell in the Sudoku board. 
* Keeps track of the possible values that can be assigned to the Cell.
*
*/

#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

class Cell{
private:
	std::vector<bool> _possibleValues;
	int _col;
	int _row;
public:
	Cell() {}
	Cell(int boardSize) : _possibleValues(boardSize, true){}
	Cell(const Cell&) = default;
	Cell& operator=(const Cell&) = delete;
	Cell(Cell&&) = delete;
	Cell&& operator=(Cell&&) = delete;

	int getValue() const;
	int getCol() const;
	int getRow() const;
	void setRow(int);
	void setCol(int);
	std::vector<int> getPossibleValues() const;
	int getPossibleValueCount() const;
	bool isPossible(int);
	void eliminateValue(int);
};

#endif