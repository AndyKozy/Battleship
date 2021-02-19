#include "Board.h"

void Board::printSpaceShift(int shift)
{
	for (int i = 0; i < shift; ++i)
		std::cout << " ";
}

void Board::printBorder()
{
	for (int i = 0; i < boardSize; ++i)
		std::cout << "+---";
	std::cout << "+";
}

void Board::changePlayer()
{
	//if Player 3of4, then -> Player 4
	if (currPlayer < numOfPlayers)
		currPlayer++;
	else //if Player 4of4, then -> Player 1
		currPlayer = 1;
}