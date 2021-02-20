/* board.h
Header for board class
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
#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<string>
#include<memory>
#include<utility>


class Board {
/// MEMBER TYPES
public:
	//using element_type = char;
	//using board_type = std::vector<element_type>;
	//using coord_type = std::tuple<int, int, int>;

public:
	void printSpaceShift(int shift);
	void printBorder();

	//shared among board games; needs to be written for each
	virtual void printBoard() = 0;
	virtual void printTopLabel(size_t &layer) = 0;
	virtual void printDiagSideLabel(size_t row) = 0;
	virtual void runGame() = 0;

	void changePlayer();

public:
	int numOfPlayers = 1;
	int currPlayer = 1;

protected:
	int whitespace = 0;
	int boardSize = 0;
	//coord_type coordinates;
};

#endif // !BOARD_H
