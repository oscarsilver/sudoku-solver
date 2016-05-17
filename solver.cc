#include "solver.h"

// Returns a pointer to the next empty Cell with fewest possible values
Cell* Solver::getNextEmptyCell(Board* b){
	Cell c = _emptyCells.top();
	_emptyCells.pop();
	return b -> getCell(c.getRow(), c.getCol());
}

void Solver::clearEmptyCells(){
	empty_cell_queue * temp = new empty_cell_queue();
	std::swap(*temp, _emptyCells);
	delete temp;
}

// Divide the cells on the board into empty and filled cells
void Solver::separateEmptyCells(Board* b){
	clearEmptyCells();
	_filledCells.clear();
	for(Cell c : b->getCells()){
		if(c.isEmpty()){
			_emptyCells.push(c);
		}
		else{
			_filledCells.push_back(c);
		}
	}
}

bool Solver::isInSameSquare(int r1, int c1, int r2, int c2, int squareSize){
	return (r1/squareSize == r2/squareSize) && (c1/squareSize == c2/squareSize);
}

void Solver::removePossibleValues(Cell* c, Board* b){
	int row = c -> getRow();
	int col = c -> getCol();
	for(Cell& filledCell : _filledCells){
		if(filledCell.getRow() == row || filledCell.getCol() == col){
			c -> eliminateValue(filledCell.getValue());
		}
		else if(isInSameSquare(row, col, filledCell.getRow(), filledCell.getCol(), b->getSquareSize())){
			c -> eliminateValue(filledCell.getValue());
		}
	}
}

bool Solver::onSolved(Board* b){
	b -> printBoard();
	delete b;
	return true;
}

bool Solver::solve(Board* board){
	if(board->isSolved()){
		return onSolved(board);
	}

	separateEmptyCells(board);
	if(_emptyCells.empty()){
		delete board;
		return false;
	}

	Cell * currentCell = getNextEmptyCell(board);
	removePossibleValues(currentCell, board);
	int nPossibleValues = currentCell -> getPossibleValueCount();

	if(nPossibleValues == 0){
		delete board;
		return false;
	}

	for(int val : currentCell -> getPossibleValues()){
		currentCell -> setValue(val);
		currentCell -> eliminateValue(val);
		Board* b = new Board(*board);
		if(solve(b)) return true;
	}
	
	delete board;
	return false;
}