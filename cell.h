/*
* Author: Oscar Silver
*
* Filename: cell.h
* Description: Represents a Cell in the Sudoku board. 
* Keeps track of the possible values that can be set in the Cell.
*
*/

#ifndef _CELL_H_
#define _CELL_H_

#include <vector>

class Cell{
private:
	int _value;
	int _row;
	int _col;
	bool _filled;
	std::vector<bool> possibleValues;
public:
	Cell() {}
	Cell(int boardSize) : _value(0), possibleValues(boardSize, true){}

	int getValue() const;
	int getRow() const;
	int getCol() const;
	std::vector<int> getPossibleValues() const;
	int getPossibleValueCount() const;

	void setValue(int);
	void setRow(int);
	void setCol(int);
	void setEmpty();

	bool isEmpty();
	void eliminateValue(int);
};

#endif