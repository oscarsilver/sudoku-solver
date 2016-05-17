#include "cell.h"

int Cell::getValue() const{
	auto it = std::find(_possibleValues.begin(), _possibleValues.end(), true);
	return it != _possibleValues.end() ? 1 + it - _possibleValues.begin() : -1;
}

int Cell::getCol() const{
	return _col;
}

int Cell::getRow() const{
	return _row;
}

void Cell::setRow(int row){
	_row = row;
}

void Cell::setCol(int col){
	_col = col;
}

/*
 *	Returns a vector containing all possible values for this cell
 */
std::vector<int> Cell::getPossibleValues() const{
	std::vector<int> values;
	for(int i = 1; i <= _possibleValues.size(); i++){
		if(_possibleValues.at(i - 1)){
			values.push_back(i);
		}
	}
	return values;
}

int Cell::getPossibleValueCount() const{
	return std::count(_possibleValues.begin(), _possibleValues.end(), true);
}

bool Cell::isPossible(int val){
	return _possibleValues.at(val - 1);
}

void Cell::eliminateValue(int value){
	_possibleValues.at(value - 1) = false;
}
