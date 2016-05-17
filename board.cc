#include "board.h"
#include <algorithm>
#include <iostream>
#include <set>

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

bool Board::isSolved(){
	for(Cell c : _cells){
		if(c.getPossibleValueCount() != 1){
			return false;
		}
	}
	return true;
}

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

bool isInSameSquare(int r1, int r2, int c1, int c2, int squareSize){
	return r1/squareSize == r2/squareSize && c1/squareSize == c2/squareSize;
}

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

// Returns true if value was successfully eliminated
bool Board::eliminate(Cell* c, int val){
	if(!c->isPossible(val)){
		return true;
	}
	c->eliminateValue(val);
	
	int nPossibleValues = c->getPossibleValueCount();

	if(nPossibleValues == 0){
		return false;
	}
	else if(nPossibleValues == 1){
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

void removeSpacesFromString(std::string& s){
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
}

void Board::initBoard(){
	int row = 0; int col = 0;
	for(int i = 0; i < getSize()*getSize(); i++){
		_cells.at(i).setRow(i/getSize());
		_cells.at(i).setCol(i % getSize());
	}
}

void Board::readBoardFromString(std::string s){
	initBoard();
	removeSpacesFromString(s);
	int i = 0, row = 0, col = 0;
	while(i < getSize()*getSize()){
		if(s.at(i) >= '1' && s.at(i) <= '9'){
			row = i/getSize();
			col = i % getSize();
			if(!assign(getCell(row, col), s.at(i) - '0')){
				std::cerr << "Invalid Sudoku board" << std::endl;
				return;
			}
			i++;
		}
		else if(s.at(i) == '0'){
			i++;
		}
	}
	printBoard();
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
			std::cout << getCell(i,j) -> getPossibleValueCount() << " ";
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
