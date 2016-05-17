#include "board.h"
#include <cassert>
#include <iostream>

Cell* Board::getCell(int row, int col){
	if(row >= getSize()){
		throw std::out_of_range("Number of rows exceeded");
	}
	else if(col >= getSize()){
		throw std::out_of_range("Number of columns exceeded");
	}
	else{
		return &_cells.at(row*_size + col);
	}
}

int Board::getSize() const{
	return _size;
}

int Board::getSquareSize() const{
	return _squareSize;
}

bool Board::isSolved() const{
	for(Cell c : _cells){
		if(c.getPossibleValueCount() != 1){
			return false;
		}
	}
	return true;
}

/*		
 *	Tries to eliminate all other values from the cell.
 *  Returns true if val was successfully assigned to the cell. 
 */
bool Board::assign(Cell* c, int val){
	for(int i = 1; i <= getSize(); i++){
		if(i != val){
			if(!eliminate(c, i)){
				return false;
			}
		}
	}
	return true;
}

/*		
 *	Returns a pointer to the Cell with least possible values
 */
Cell* Board::getMostConstrainedCell(){
	int nPossibleValues = getSize();
	int minCell = 0;
	for(int i = 0; i < _cells.size(); i++){
		if(_cells.at(i).getPossibleValueCount() < nPossibleValues && _cells.at(i).getPossibleValueCount() > 1){
			nPossibleValues = _cells.at(i).getPossibleValueCount();
			minCell = i;
		}
	}
	return &_cells.at(minCell);
}


/*		
 *	Returns true if val is successfully eliminated from all cells in the same
 *  row as the cell corresponding to row and col
 */
bool Board::eliminateRow(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		if(i == row){
			continue;
		}
		else if(!eliminate(getCell(i, col), val)){
			return false;
		}
	}
	return true;
}

/*		
 *	Returns true if val is successfully eliminated from all cells in the same
 *  column as the cell corresponding to row and col
 */
bool Board::eliminateCol(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		if(i == col){
			continue;
		}
		else if(!eliminate(getCell(row, i), val)){
			return false;
		}
	}
	return true;
}

/*
 *	Returns true if two cells are in the same square
 */
bool isInSameSquare(int r1, int r2, int c1, int c2, int squareSize){
	return r1/squareSize == r2/squareSize && c1/squareSize == c2/squareSize;
}

/*		
 *	Returns true if val is successfully eliminated from all cells in the same
 *  square as the cell corresponding to row and col
 */
bool Board::eliminateSquare(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getSize(); j++){
			if(isInSameSquare(row, i, col, j, getSquareSize())){
				if(i == row && j == col){
					continue;
				}
				else if(!eliminate(getCell(i,j), val)){
					return false;
				}
			}
		}
	}
	return true;
}

/*		
 *	Returns true if the value is successfully eliminated from the cell
 */
bool Board::eliminate(Cell* c, int val){
	if(!c->isPossible(val)){
		// The value is already eliminated
		return true;
	}
	c->eliminateValue(val);
	
	int nPossibleValues = c->getPossibleValueCount();

	if(nPossibleValues == 0){
		// Should not remove the last possible value of a cell
		return false;
	}
	else if(nPossibleValues == 1){
		// If there is only one remaining value it should be removed from all
		// other cells in the same row, column and square as this cell
		if(!eliminateRow(c->getRow(), c->getCol(), c->getValue())){
			return false;
		}
		else if(!eliminateCol(c->getRow(), c->getCol(), c->getValue())){
			return false;
		}
		else if(!eliminateSquare(c->getRow(), c->getCol(), c->getValue())){
			return false;
		}
	}
	return true;
}

/*		
 *	Sets row and column number for all cells
 */
void Board::initBoard(){
	int row = 0; int col = 0;
	for(int i = 0; i < getSize()*getSize(); i++){
		_cells.at(i).setRow(i/getSize());
		_cells.at(i).setCol(i % getSize());
	}
}

/*		
 *	Intializes a board and assigns values to it
 *  from the input string
 */
void Board::readBoardFromString(std::string s){
	initBoard();
	int i = 0, row = 0, col = 0;
	while(i < getSize()*getSize()){
		if(s.at(i) >= '1' && s.at(i) <= '9'){
			row = i/getSize();
			col = i % getSize();
			assert(assign(getCell(row, col), s.at(i) - '0'));
			i++;
		}
		else if(s.at(i) == '0' || s.at(i) == '.'){
			i++;
		}
	}
}

void printHorizontalLine(std::string separator, int length){
	for(int i = 1; i < length; i++){
		std::cout << separator;
	}
}

void Board::printBoard(){
	printHorizontalLine("==", getSize() + getSquareSize());
	std::cout << std::endl;
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getSize(); j++){
			if(getCell(i,j) -> getPossibleValueCount() > 1){
				std::cout << ". ";
			}
			else{
				std::cout << getCell(i,j) -> getValue() << " ";
			}
			if((j + 1) % getSquareSize() == 0 && j + 1 != getSize()){
				std::cout << "| ";
			}
		}
		if((i + 1) % getSquareSize() == 0 && i + 1 != getSize()){
			std::cout << std::endl;
			printHorizontalLine("- ", getSize() + getSquareSize());
		}
		std::cout << std::endl;
	}
	printHorizontalLine("==", getSize() + getSquareSize());
	std::cout << std::endl;
}
