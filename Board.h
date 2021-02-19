#ifndef BOARD_H
#define BOARD_H

#include<iostream>
#include<string>
#include<memory>


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
	virtual void printDiagSideLabel(size_t &row) = 0;
	

	void changePlayer();

	int gameState;

public:
	int numOfPlayers;
	int currPlayer = 1;

protected:
	int whitespace;
	int boardSize;
	coord_type coordinates;
};


struct BBPiece {
	const std::string name;
	const size_t size;
	int count;
};

#endif // !BOARD_H
