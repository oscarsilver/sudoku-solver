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

const int BOARD_SIZE = 9;
const int SQUARE_SIZE = 3;

class Board{
private:
	int _size;
	int _squareSize;
	std::vector<Cell> _cells;

	/*		
 	 *	Returns true if val is successfully eliminated from all cells in the same
 	 *  square as the cell corresponding to row and col
 	 */
	bool eliminateRow(int, int, int);

	/*		
 	 *	Returns true if val is successfully eliminated from all cells in the same
 	 *  column as the cell corresponding to row and col
 	 */
	bool eliminateCol(int, int, int);

	/*		
 	 *	Returns true if val is successfully eliminated from all cells in the same
 	 *  row as the cell corresponding to row and col
 	 */
	bool eliminateSquare(int, int, int);

	/*		
	 *	Sets row and column number for all cells
 	 */
	void initBoard();
public:
	Board() : _size(BOARD_SIZE), _squareSize(SQUARE_SIZE), _cells(BOARD_SIZE*BOARD_SIZE, Cell(BOARD_SIZE)){}
	~Board() = default;
	Board(const Board&) = default;
	Board& operator=(Board&) = default;
	Board(Board&&) = delete;
	Board& operator=(Board&&) = delete;

	/*
	 *	Returns a pointer to a cell corresponding to row and column
	 */
	Cell* getCell(int, int);

	/*		
 	 *	Returns a pointer to the Cell with least possible values
 	 */
	Cell* getMostConstrainedCell();
	int getSize() const;
	int getSquareSize() const;
	bool isSolved() const;

	/*		
 	 *	Tries to assign a value to the cell by eliminating all other values
 	 *  from the cell. Returns true if val was successfully assigned to the
 	 *  cell.
 	 */
	bool assign(Cell*, int);

	/*		
 	 *	Returns true if the value is successfully eliminated from the cell
     */
	bool eliminate(Cell*, int);

	/*		
	 *  Intializes a board and assigns values to it
 	 *  from the input string
 	 */
	bool readBoardFromString(std::string);
	void printBoard();
};

#endif