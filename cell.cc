#include "cell.h"

int Cell::getValue() const{
	return _value;
}

int Cell::getRow() const{
	return _row;
}

int Cell::getCol() const{
	return _col;
}

std::vector<int> Cell::getPossibleValues() const{
	std::vector<int> values;
	for(int i = 1; i <= possibleValues.size(); i++){
		if(possibleValues.at(i - 1)){
			values.push_back(i);
		}
	}
	return values;
}

int Cell::getPossibleValueCount() const{
	int res = 0;
	for(bool b : possibleValues){
		if(b) res++;
	}
	return res;
}

void Cell::setRow(int row){
	_row = row;
}

void Cell::setCol(int col){
	_col = col;
}

void Cell::setValue(int value){
	_value = value;
	if(_value != 0){
		_filled = true;
	}
}

void Cell::setEmpty(){
	_value = 0;
	_filled = false;
}

bool Cell::isEmpty(){
	return !_filled;
}

void Cell::eliminateValue(int value){
	possibleValues.at(value - 1) = false;
}
