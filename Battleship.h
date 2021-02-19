#ifndef BATTLESHIP3D_H
#define BATTLESHIP3D_H

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <string>
#include <map>

#include <algorithm>
#include <utility>

#include "Board.h"

void runGame();

/*
struct BBPiece {
	const static std::string name;
	const static size_t size;
	int amount;
};*/

class Battleship3D : public Board {
///MEMBER TYPES
public:
	using element_type = char;
	using board_type = std::vector<element_type>;
	using coord_type = std::tuple<int, int, int>;
	
	using key_type = std::string;
	//using element_type = BBPiece;
	//using inventory_type = std::map<key_type, element_type>;

public:
	/*BBMarker
	* Battleship (Bad-Boy) Markers
	* Change the ASCII here if you want a different look
	* [Usage]: BBMarkerType::ERROR etc.
	*/
	typedef enum BBMarkerType {
			EMPTY = ' ',
			MISS  = '_',
			HIT   = 'X',
			PIECE = '#',
			SHOT  = '/',
			ERROR = 'Æ',
	};
	/*
	inventory_type inventory{	{"carrier",		{"Carrier",		5,	1}},
								{"battleship",	{"Battleship",	4,	2}},
								{"destroyer",	{"Destroyer",	3,	1}},
								{"submarine",	{"Submarine",	3,	2}},
								{"patrolboat",	{"Patrol Boat",	2,	4}} };
								*/

//CONSTRUCTORS
	//Battleship3D();

//INHERITED PRINT FUNCTIONS
public:
	void printBoard();
	void printTopLabel(size_t &layer);
	void printDiagSideLabel(size_t& row);

	void makeBoard();
public:
	//void placePieces();
	void checkShot(board_type &firstBoard, board_type &secondBoard, size_t &shotCoords);
	void shootPiece();
	void checkWin();

///ACCESSORS
public:
	//coord_type getCoordinates();
	std::string getPieceName();
///MUTATORS
	void setCoordinates();

///MEMBER VARIABLES
public:
	bool ifShot;
public:
	const int boardDepth = 3;
	size_t  _x = 0,
			_y = 0,
			_z = 0;

	board_type currBoard;
	board_type playerBoard2;
	board_type playerBoard1;
};

#endif // !BATTLESHIP3D_H