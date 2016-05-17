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

std::vector<Cell> Board::getCells() const{
	return _cells;
}

void Board::setEmptyBoard(){
	for(Cell& c : _cells){
		c.setEmpty();
	}
}

bool Board::isSolved(){
	bool solved = false;
	for(int i = 0; i < getSize(); i++){
		solved = isRowSolved(i) && isColSolved(i);
	}
	return solved && isSquareSolved();
}

bool Board::isRowSolved(int row){
	std::set<int> filled;
	int val;
	for(int j = 0; j < getSize(); j++){
		val = getCell(row,j) -> getValue();
		if(val != 0){
			filled.insert(val);
		}
	}
	return filled.size() == getSize();
}

bool Board::isColSolved(int col){
	std::set<int> filled;
	int val;
	for(int i = 0; i < getSize(); i++){
		val = getCell(i, col) -> getValue();
		if(val != 0){
			filled.insert(val);
		}
	}
	return filled.size() == getSize();
}

bool Board::isSquareSolved(){
	std::set<int> filled;
	int val;
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getSize(); j++){
			val = getCell((i/3)*3 + j/3, i*3 % 9 + j % 3) -> getValue();
			if(val != 0){
				filled.insert(val);
			}
		}
	}
	return filled.size() == getSize();
}

void removeSpacesFromString(std::string& s){
	s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
}

void Board::readBoardFromString(std::string s){
	setEmptyBoard();
	removeSpacesFromString(s);
	if(s.size() < getSize()*getSize()){
		throw std::exception();
	}
	int row, col, i = 0;
	while(i < getSize()*getSize()){
		row = i/getSize();
		col = i % getSize();
		getCell(row,col) -> setValue(s.at(i) - '0');
		getCell(row,col) -> setRow(row);
		getCell(row,col) -> setCol(col);
		i++;
	}
}

void printHorizontalLine(std::string style, int length){
	for(int i = 0; i < length; i++){
		std::cout << style;
	}
}

void Board::printBoard(){
	for(int i = 0; i < getSize(); i++){
		for(int j = 0; j < getSize(); j++){
			std::cout << getCell(i,j) -> getValue() << " ";
			if((j + 1) % getSquareSize() == 0){
				std::cout << "| ";
			}
		}
		if((i + 1) % getSquareSize() == 0){
			std::cout << std::endl;
			printHorizontalLine("- ", getSize() + getSquareSize());
		}
		std::cout << std::endl;
	}
	printHorizontalLine("==", getSize() + getSquareSize());
	std::cout << std::endl;
}
