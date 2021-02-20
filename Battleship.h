/* battleship.h
Header for Battleship class
	A class for a battleship game with multiple boards and shared 
	Submission For Project 1
	
Course : CS372 - Software Construction(Spring 2021)
Instructor : Dr. Chris Hartman

@author Andrew Kozak
		Timothy Albert Kline
@version 1.0

Started: 2021-02-04
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
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

//Streams
#include <iostream>
#include <iomanip>
#include <sstream>
//Class Templates
#include <vector>
#include <string>
#include <map>
//STL
#include <algorithm>

//Headers
#include "Board.h"


/*struct BBPiece
* DESCR.:
	A data structure for a Battleship game piece
*/
struct BBPiece {
	const std::string name;		//name of the game piece
	const size_t size;			//size of the game piece
	int count;					//the number of game pieces
};


/*Battleship3D
* DESCR.:
 	Constructs a multi-layered, shared board, Battleship game
	Inherits from the Board (almost-factory) class
	[USAGE]: make a Battleship object and call .runGame()
* 
*/
class Battleship3D : public Board {
///MEMBER ENUMS
protected:
	/*BBMarker
	* Battleship (Bad-Boy) Markers enum class.
	* Change the ASCII here if you want a different look.
	* [USAGE]: BBMarkerType::ERROR
			   char(BBMarkerType::PIECE)  -- to print
	*/
	enum class BBMarkerType {
		EMPTY	= ' ',
		MISS	= '_',
		HIT		= 'X',
		PIECE	= '#',
		SHOT	= '/',
		ERROR	= 'Æ',
	};

	/*BBGameState
	* Enum class for state machine.
	* [USAGE]: BBGameState::ERROR
	* [TO DO]: Streamline to Board class for future games
	*/
	enum class BBGameState {
		START, P1_WIN, P2_WIN, TIE, END, ERROR
	};

	/*BBDirection
	* Enum for the orientation of a game piece.
	* To get rid of magic numbers/chars.
	* [USAGE]: BBDirection::ERROR
	*/
	enum class BBDirection {
		VERTICAL = 'v',
		HORIZONTAL = 'h',
		ERROR = ' '
	};

	/*BBAmount
	* Enum for the number of pieces for each ship
	* [USAGE] In tandem with invetory (see placePieces())
	*/
	enum BBAmount {
		CARRIER		= 1,
		BATTLESHIP	= 2,
		DESTROYER	= 1,//totals
		SUBMARINE	= 2,//to 3
		PATROL		= 4,
	};

///MEMBER TYPES
public:
	/*board
	* member types for the game board
	*/
	using element_type = BBMarkerType;
	using board_type = std::vector<element_type>;
	using coord_type = std::tuple<int, int, int>;
	/*inventory
	* see placePiece()
	*/
	using key_type = std::string;
	using piece_type = BBPiece;
	using inventory_type = std::map<key_type, piece_type>;


///CONSTRUCTORS
	Battleship3D() {};
	Battleship3D(const Battleship3D& other) = default;
	Battleship3D(Battleship3D&& other) = default;
	Battleship3D& operator=(const Battleship3D& other) = default;
	Battleship3D& operator=(Battleship3D&& other) = default;
	~Battleship3D() = default;


///INHERITED FUNCTIONS
public:
	///PRINT
	void printBoard();
	void printTopLabel(size_t &layer);
	void printDiagSideLabel(size_t row);
	void runGame();

///MEMBER FUNCTIONS
public:
	//SETUP
	void makeBoard();
	void setupPieces(board_type &board);
	void switchBoards();

	//PLACE PIECE
	bool checkForPlacedPieces(const int& boatSize, const BBDirection direction);
	void placeOnePiece(const int &boatSize, const BBDirection direction);
	//void verticalPlacePiece(int boatSize);
	//void horizontalPlacePiece(int boatSize);
	board_type placePieces();

	//SHOOT PIECE
	void checkShot(board_type &firstBoard, board_type &secondBoard, size_t &shotCoords);
	void shootPiece();
	void checkWin();

///ACCESSORS
public:
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
	//Shot/Placement Coordinates
	size_t  _x = 0,
			_y = 0,
			_z = 0;
};

#endif // !BATTLESHIP_H