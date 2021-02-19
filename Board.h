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
	using coord_type = std::tuple<int, int, int>;

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
	coord_type coordinates;
};

#endif // !BOARD_H
