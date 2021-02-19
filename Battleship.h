#ifndef BATTLESHIP3D_H
#define BATTLESHIP3D_H

//Streams
#include <iostream>
#include <iomanip>
#include <sstream>
//Containers
#include <vector>
#include <string>
#include <map>
//Library
#include <algorithm>
#include <utility>
//Header
#include "Board.h"

//void runGame();

struct BBPiece {
	const std::string name;
	const size_t size;
	int count;
};


class Battleship3D : public Board {
///MEMBER ENUMS
public:
	/*BBMarker
	* Battleship (Bad-Boy) Markers
	* Change the ASCII here if you want a different look
	* [Usage]: BBMarkerType::ERROR etc.
	*/
	enum class BBMarkerType {
		EMPTY = ' ',
		MISS = '_',
		HIT = 'X',
		PIECE = '#',
		SHOT = '/',
		ERROR = 'Æ',
	};

	enum class BBGameState {
		START, P1_WIN, P2_WIN, TIE, END, ERROR
	};

	
///MEMBER TYPES
public:
	using element_type = BBMarkerType;
	using board_type = std::vector<element_type>;
	using coord_type = std::tuple<int, int, int>;

	using key_type = std::string;
	using piece_type = BBPiece;
	using inventory_type = std::map<key_type, piece_type>;


//CONSTRUCTORS
	Battleship3D() {}

//INHERITED PRINT FUNCTIONS
public:
	void printBoard();
	void printTopLabel(size_t &layer);
	void printDiagSideLabel(size_t row);

	void runGame();
	void makeBoard();
public:
	void setupPieces(board_type &board);
	void switchBoards();
	bool checkForPlacedPieces(const int& boatSize, const char& orientation);
	void placeOnePiece(const int &boatSize, const char &orientation);
	board_type placePieces();
	//void verticalPlacePiece(int boatSize);
	//void horizontalPlacePiece(int boatSize);
	void checkShot(board_type &firstBoard, board_type &secondBoard, size_t &shotCoords);
	void shootPiece();
	void checkWin();

///ACCESSORS
public:
	//coord_type getCoordinates();
	std::string getPlayerString();
	int getPosition(size_t x, size_t y, size_t z);

///MUTATORS
	void setCoordinates();

///MEMBER VARIABLES
public:
	bool ifShot = false;
	BBGameState currState = BBGameState::START;
protected:
	board_type currBoard;
	board_type playerBoard1;
	board_type playerBoard2;
private:
	const int boardDepth = 3;
	size_t  _x = 0,
			_y = 0,
			_z = 0;
};

#endif // !BATTLESHIP3D_H