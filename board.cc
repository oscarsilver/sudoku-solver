#include "board.h"
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
	for(Cell cell : _cells){
		if(cell.getPossibleValueCount() != 1){
			return false;
		}
	}
	return true;
}

bool Board::assign(Cell* cell, int val){
	for(int i = 1; i <= getSize(); i++){
		if(i != val){
			if(!eliminate(cell, i)){
				return false;
			}
		}
	}
	return true;
}

Cell* Board::getMostConstrainedCell(){
	int nPossibleValues = getSize();
	int minCell = 0;
	for(int i = 0; i < _cells.size(); i++){
		// This cell is already eliminated
		if(_cells.at(i).getPossibleValueCount() < nPossibleValues && _cells.at(i).getPossibleValueCount() > 1){
			nPossibleValues = _cells.at(i).getPossibleValueCount();
			minCell = i;
		}
	}
	return &_cells.at(minCell);
}

bool Board::eliminateRow(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		if(i == row){
			// This cell is already eliminated
			continue;
		}
		else if(!eliminate(getCell(i, col), val)){
			return false;
		}
	}
	return true;
}

bool Board::eliminateCol(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		if(i == col){
			// This cell is already eliminated
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

bool Board::eliminateSquare(int row, int col, int val){
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getSize(); j++){
			if(isInSameSquare(row, i, col, j, getSquareSize())){
				if(i == row && j == col){
					// Don't eliminate this cell twice
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

bool Board::eliminate(Cell* cell, int val){
	if(!cell->isPossible(val)){
		// The value is already eliminated
		return true;
	}
	cell->eliminateValue(val);
	
	int nPossibleValues = cell->getPossibleValueCount();

	if(nPossibleValues == 0){
		// Should not remove the last possible value of a cell
		return false;
	}
	else if(nPossibleValues == 1){
		// If there is only one remaining value it should be removed from all
		// other cells in the same row, column and square as this cell
		if(!eliminateRow(cell->getRow(), cell->getCol(), cell->getValue())){
			return false;
		}
		else if(!eliminateCol(cell->getRow(), cell->getCol(), cell->getValue())){
			return false;
		}
		else if(!eliminateSquare(cell->getRow(), cell->getCol(), cell->getValue())){
			return false;
		}
	}
	return true;
}

void Board::initBoard(){
	int row = 0; int col = 0;
	for(int i = 0; i < getSize()*getSize(); i++){
		_cells.at(i).setRow(i/getSize());
		_cells.at(i).setCol(i % getSize());
	}
}

bool Board::readBoardFromString(std::string s){
	initBoard();
	int i = 0, row = 0, col = 0;
	while(i < getSize()*getSize()){
		if(s.at(i) >= '1' && s.at(i) <= '9'){
			row = i/getSize();
			col = i % getSize();
			if(!assign(getCell(row,col), s.at(i) - '0')){
				return false;
			}
			i++;
		}
		else if(s.at(i) == '0' || s.at(i) == '.'){
			i++;
		}
	}
	return true;
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
				// Cell is not set yet
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
