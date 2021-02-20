/* board.cpp
Source for board class
	A class for future projects involving board games
	Unfinished attempt at Factory class application
	Used by Battleship class
	Submission For Project 1

Course : CS372 - Software Construction(Spring 2021)
Instructor : Dr. Chris Hartman

@author Andrew Kozak
		Timothy Albert Kline
@version 1.0

Started: 2021-02-17
Updated: 2021-02-19

*************************************************************
* Source code largely written by Timothy Albert Kline & Andrew Kozak.
* The following references are indicated below.
* Any code reproduced from another source is indicated above
* the comment section of a function or class.
*
* Source references/material:
* C++ Primer - Stanley B. Lippman (2013)
* cppreference.com
* cplusplus.com
*/
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