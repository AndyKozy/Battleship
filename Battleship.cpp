/* battleship.cpp
Source for Battleship class
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
#include "Battleship.h"

/*
Board Positions:
'#':Player Ship
' ':Empty Space
'_':Miss
'X':Hit
'/':Enemy Shot
*/

/*
Order of making things:
1.Board :D
2.Shooting :D
3.Checking a win :D
4.Placing Pieces D:
5.Graphics
6.Seperating
7.Network
*/

///			Clementine The Beaver
///				  ___
///			   .="   "=._.---.
///			 ."         C ' y'`D
///			/   ,       `.  w_/
///		   |   '-.   /     / 
///  _,..._|      )_-\ \_=.\
/// `-....-'`------)))`=-'"`'"

using board_type = Battleship3D::board_type;

/*makeBoard
* This makes the two board
*/
void Battleship3D::makeBoard()
{
	boardSize = 8;
	currState = BBGameState::START;
	ifShot = false;
	for (auto i = 0; i < pow(boardSize, 2) * boardDepth; i++)
	{
		playerBoard1.push_back(BBMarkerType::EMPTY);
		playerBoard2.push_back(BBMarkerType::EMPTY);
	}

	std::cout << "Board size is: ";
	for (int i = 0; i < 2; ++i)
		std::cout << boardSize << 'x';
	std::cout << boardDepth << std::endl;
	system("PAUSE");
}

///ACCESSORS
/*getPlayerString
* Gets input from player to a string
* @returns gamePiece, the tranformed string
*/
std::string Battleship3D::getPlayerString()
{
	std::string gamePiece;
	std::getline(std::cin, gamePiece);														//grab the string with getline()
	std::transform(gamePiece.begin(), gamePiece.end(), gamePiece.begin(), std::tolower);	//turn all chars to lowercase
	gamePiece.erase(remove(gamePiece.begin(), gamePiece.end(), ' '), gamePiece.end());		//remove whitespace
	return gamePiece;
}

/*getPosition
* Simple function that returns the equation result for a 1D array for a 3D index
*/
int Battleship3D::getPosition(size_t x, size_t y, size_t z)
{
	return x + boardSize * y + pow(boardSize, 2) * z;
}
///MUTATORS
/*setCoordinates
* Sets the member variable coordinates from user input
* Handles out of bound inputs
* Board.coordinates stores these values as well [UNUSED]
*/
void Battleship3D::setCoordinates()
{
	while (true)
	{
		std::string temp = "";
		std::getline(std::cin, temp);
		std::stringstream sstream(temp);
		sstream >> _x >> _y >> _z;
		if (_x >= boardSize || _y >= boardSize || _z >= boardDepth)
			std::cout << "Invalid Coordinates: " << std::endl;
		else
			break;
	}
	//coordinates = std::make_tuple(_x, _y, _z);
}

///SHOOT BOARD FUNCTIONS
/*checkShot
* Checks how the coordinates of a shot affects both player boards
*/
void Battleship3D::checkShot(board_type& firstBoard, board_type& secondBoard, size_t& position)
{
	if (firstBoard[position] == BBMarkerType::PIECE)
	{
		firstBoard[position] = BBMarkerType::HIT;
		ifShot = true;
	}
	else
		firstBoard[position] = BBMarkerType::MISS;

	if (secondBoard[position] == BBMarkerType::PIECE)
	{
		firstBoard[position] = BBMarkerType::HIT;
		ifShot = true;
	}
	secondBoard[position] = BBMarkerType::SHOT;
}

/*shootPiece
* Shoot the board given user coordinates
*/
void Battleship3D::shootPiece()
{
	ifShot = false;
	size_t shotCoords;

	//Determining if shot has been made
	while (true)
	{
		setCoordinates();
		shotCoords = getPosition(_x,_y,_z);

		if (playerBoard1[shotCoords] != BBMarkerType::PIECE && 
			playerBoard1[shotCoords] != BBMarkerType::EMPTY)
			std::cout << "Shot already made. Enter new shot: ";
		else
			break;
	}

	//Updates the boards
	switch (currPlayer)
	{
	case 1:
		checkShot(playerBoard1, playerBoard2, shotCoords);
		break;
	case 2:
		checkShot(playerBoard2, playerBoard1, shotCoords);
		break;
	default:
		std::cout << "Shouldn't print this. Check for error." << std::endl;
		break;
	}
}

///PRINT BOARD FUNCTIONS
/*printTopLabel
* Prints the board notation for the horizontal axis 
*/
void Battleship3D::printTopLabel(size_t &layer)
{
	whitespace = 1;
	const char STRT_CHAR = '0';
	
	char notationChar = STRT_CHAR;

	std::cout << "LAYER " << layer << std::endl;
	printSpaceShift(whitespace);
	for (notationChar; notationChar < (boardSize + STRT_CHAR); ++notationChar)
		std::cout << "  " << notationChar << " ";
	std::cout << "\n";
}

/*printDiagSideLabel
* Prints the board notation for the vertical (diagonalized) axis
*/
void Battleship3D::printDiagSideLabel(size_t row)
{
	printSpaceShift(whitespace);
	printBorder();
	std::cout << "\n";
	whitespace--;
	printSpaceShift(whitespace);
	std::cout << row << " ";
}

/*printBoard
* Prints the player's board
*/
void Battleship3D::printBoard()
{
	for (size_t z = 0; z < boardDepth; z++)
	{
		printTopLabel(z);
		for (size_t y = 0; y < boardSize; y++)
		{
			printDiagSideLabel(y);
			for (size_t x = 0; x < boardSize; x++)
			{
				//a switch within a switch statement, because why not? >:D //LMAO YOU THOUGHT YOU COULD SWITCH ME NONONO I MADE THE ENTIRE SWITCH STATEMENT 1 LINE MUAHAHAHAHAHAH
				//touché, but the spacing was off >:P
				std::cout << "\\ " << char(currBoard[getPosition(x, y, z)]) << ' ';
			}
			std::cout << "\\" << std::endl;
			
			whitespace += 3;
		}
		printSpaceShift(whitespace);
		printBorder();
		std::cout << std::endl << std::endl;
	}
}

//Vertical and Horizontal Placement
//Handled by placeOnePiece()
/*
void Battleship3D::verticalPlacePiece(int boatSize)
{
	int endOfShip;
	int outOfBoard;
	std::cout << "Where would you like the top of you piece placed: ";
	while (true)
	{
		setCoordinates();
		endOfShip = getPosition(_x, (_y + boatSize - 1), _z);
		outOfBoard = getPosition(_x, 0, (_z + 1));
		
		if (endOfShip >= outOfBoard || endOfShip >= currBoard.size())
			std::cout << "Invalid Placement: ";
		else
		{
			int n = 0;
			for (int i = 0; i < boatSize; i++)
			{
				if (currBoard[getPosition(_x, (_y + i), _z)] == BBMarkerType::PIECE)
					n++;
			}
			if (n == 0)
				break;
			else
				std::cout << "A piece is there, enter new location: ";
		}
	}
	for (int i = 0; i < boatSize; i++)
	{
		currBoard[getPosition(_x, (_y + i), _z)] = BBMarkerType::PIECE;
	}
}

void Battleship3D::horizontalPlacePiece(int boatSize)
{
	int endOfShip;
	int outOfBoard;
	std::cout << "Where would you like the left of you piece placed: ";
	while (true)
	{
		setCoordinates();
		endOfShip = getPosition((_x + boatSize - 1), _y, _z);
		outOfBoard = getPosition(0,(_y + 1), _z);

		if (endOfShip >= outOfBoard || endOfShip >= currBoard.size())
			std::cout << "Invalid Placement: ";
		else
		{
			//if I declare it within the for-loop, it only exists in the for-loop
			int n = 0;
			for (int i = 0; i < boatSize; i++)
			{
				if (currBoard[getPosition((_x + i), _y, _z)] == BBMarkerType::PIECE)
					n++;
			}
			if (n == 0)
				break;
			else
				std::cout << "A piece is there, enter new location: ";
		}
	}
	for (int i = 0; i < boatSize; i++)
	{
		currBoard[getPosition((_x+i),_y,_z)] = BBMarkerType::PIECE;
	}
}
*/

///PLACE PIECE FUNCTIONS
/*checkForPlacedPiece
* Checks if a placed piece is within the range of a new piece's size
* @returns true if found
*/
bool Battleship3D::checkForPlacedPieces(const int& boatSize, const BBDirection direction)
{
	for (int i = 0; i < boatSize; i++)
	{
		//for the sake of "switching" to the correct orientation
		//without testing each condition of an if-elseif statement
		switch (direction)
		{
		case BBDirection::VERTICAL:
			if (currBoard[getPosition(_x, (_y + i), _z)] == BBMarkerType::PIECE) return true;
			break;
		case BBDirection::HORIZONTAL:
			if (currBoard[getPosition((_x + i), _y, _z)] == BBMarkerType::PIECE) return true;
			break;
		default:
			break; //should not run
		}
	}
	return false;
}

/*placeOnePiece
* Based on the orientation, a piece is placed on the board
*/
void Battleship3D::placeOnePiece(const int &boatSize, const BBDirection direction)
{
	int endOfShip = 0;
	int outOfBoard = 0;
	bool pieceExists = false;
	
	std::cout << " of your piece placed: ";
	do
	{
		setCoordinates();
		
		if (direction == BBDirection::VERTICAL)
		{
			endOfShip = getPosition(_x, (_y + boatSize - 1), _z);
			outOfBoard = getPosition(_x, 0, (_z + 1));
		}
		else if (direction == BBDirection::HORIZONTAL)
		{
			endOfShip = getPosition((_x + boatSize - 1), _y, _z);
			outOfBoard = getPosition(0, (_y + 1), _z);
		}

		if (endOfShip >= outOfBoard || endOfShip >= currBoard.size())
		{
			//std::cout << "Invalid Placement: ";
			//compensate
			if (direction == BBDirection::VERTICAL)
			{
				//From: [boatSize * ((endOfShip-outOfBoard)/boatSize) + 1)]/boardSize + 1
				auto shiftUp = (endOfShip - outOfBoard + boatSize)/boardSize + 1;
				_y -= shiftUp;
			}
			else if (direction == BBDirection::HORIZONTAL)
			{
				auto shiftLeft = endOfShip - outOfBoard + 1;
				_x -= shiftLeft;
			}
			pieceExists = checkForPlacedPieces(boatSize, direction);
			std::cout << "Piece placement compensated." << std::endl;
		}
		else
		{
			pieceExists = checkForPlacedPieces(boatSize, direction);
		}
		
		if (pieceExists)
			std::cout << "A piece is there, enter new location: ";
	} while (pieceExists);
	
	for (int i = 0; i < boatSize; i++)
	{
		switch (direction)
		{
		case BBDirection::HORIZONTAL:
			currBoard[getPosition((_x + i), _y, _z)] = BBMarkerType::PIECE;
			break;
		case BBDirection::VERTICAL:
			currBoard[getPosition(_x, (_y + i), _z)] = BBMarkerType::PIECE;
			break;
		default:
			break;
		}
	}
}

/*placePieces
* Updates the current player board and places 
*/
board_type Battleship3D::placePieces()
{
	inventory_type inventory{		{"c",	{"Carrier",		5,    BBAmount::CARRIER}},
									{"b",	{"Battleship",	4,    BBAmount::BATTLESHIP}},
									{"d",	{"Destroyer",	3,    BBAmount::DESTROYER}},
									{"s",	{"Submarine",	3,    BBAmount::SUBMARINE}},
									{"p",	{"Patrol Boat",	2,    BBAmount::PATROL}} };

	int totPieces = 0;
	for (const auto& [key, boat] : inventory) totPieces += boat.count;
	
	//iomanip formatting stuff
	//const char delimiter = ' ';
	//const int nameWid = 12;
	const int quantWid = 5;

	int piecesPlaced = 0;
	
	std::string orientation = "";
	
	while (piecesPlaced < totPieces)
	{
		system("cls"); //Remove this(?) if graphics get put in
		printBoard();
		std::cout << "Player " << currPlayer << " pick a game piece: " << std::endl;

		//Print the inventory
		std::cout << "| ";
		for (const auto& [key, boat] : inventory)
			std::cout << std::left << "(" << key << ")"
			<< boat.name
			<< " x" << boat.count
			<< std::right << std::setw(quantWid) << " [" << boat.size << ']' << " | ";
		std::cout << std::endl;
		
		auto itr = inventory.find(getPlayerString()); //grab the string input and search through the inventory
		if (itr != inventory.end())
		{
			auto& boat = itr->second; //for readability's sake
			if (boat.count > 0)
			{
				//Print selection
				std::cout << "[SELECTION]: " << boat.name << " (size " << boat.size << ")\n"
					<< "[REMAINING]: " << boat.count << std::endl;
				//TODO: prompt comfirmation of selected piece b4 asking where to place
				std::cout << "Would you like to place your piece vertically or horizontally [v/h]: ";
				while (true)
				{
					orientation = getPlayerString();
					if (orientation == "vertically" || orientation == "vertical" || orientation == "v")
					{
						std::cout << "Where would you like the top";
						placeOnePiece(boat.size, BBDirection::VERTICAL);
						//verticalPlacePiece(boat.size);
						break;
					}
					else if (orientation == "horizontally" || orientation == "horizontal" || orientation == "h")
					{
						std::cout << "Where would you like the left";
						placeOnePiece(boat.size, BBDirection::HORIZONTAL);
						//horizontalPlacePiece(boat.size);
						break;
					}
					else
						std::cout << "Invalid input. Please re-enter your choice: ";
				}
			}
			else
			{
				std::cout << "You've already placed these pieces." << std::endl;
				system("pause"); //REMOVE WHEN GRAPHICS ARE USED
				continue;
			}
			//if successful, reduce quantity and ++piecesPlaced
			boat.count--;
			++piecesPlaced;
		}
		else
		{
			std::cout << "Not a valid game piece. Try again." << std::endl;
			system("pause");
		}
	}
	return currBoard;
}

///SETUP
/*setupPieces
* Prompts for the place piece functions above
*/
void Battleship3D::setupPieces(board_type &board)
{
	switchBoards();
	board = placePieces();
	system("CLS");
	printBoard();
	changePlayer();
	std::cout << "Please pass the game to Player " << currPlayer << std::endl;
	system("PAUSE");
}

/*switchBoards
* Switches to the currPlayer's board
*/
void Battleship3D::switchBoards()
{
	switch (currPlayer)
	{
	case 1:
		currBoard = playerBoard1;
		break;
	case 2:
		currBoard = playerBoard2;
		break;
	default:
		std::cout << "[ERROR]: Too many players set for this game. Please check Board.numOfPlayers."
			<< std::endl;
		break;
	}
}

void Battleship3D::checkWin()
{
	bool gameEnd1 = true;
	bool gameEnd2 = true;
	for (auto& n : playerBoard1)
	{
		if (n == BBMarkerType::PIECE)
			gameEnd1 = false;
	}
	for (auto& n : playerBoard2)
	{
		if (n == BBMarkerType::PIECE)
			gameEnd2 = false;
	}

	if (!gameEnd1 && gameEnd2)
		currState = BBGameState::P1_WIN;
	else if (gameEnd1 && !gameEnd2)
		currState = BBGameState::P2_WIN;
	else if (gameEnd1 && gameEnd2)
		currState = BBGameState::TIE;
	else
		currState = BBGameState::START;
}

/*runGame
* Runs the game (state machine) loop
*/
void Battleship3D::runGame()
{
	std::cout << "Starting Battleship3D game..." << std::endl;

	numOfPlayers = 2;
	makeBoard();

	currPlayer = 1;
	setupPieces(playerBoard1);
	setupPieces(playerBoard2);

	while (currState != BBGameState::END)
	{
		switchBoards();
		system("CLS");
		printBoard();

		//A switch statement, cuz I know you don't like 'em >:D
		std::cout << "Player " << currPlayer << "\n";
		std::cout << "Where would you (" << currPlayer << ") like to shoot: [x y z] ";
		
		shootPiece();
		if (ifShot)
			std::cout << "Hit!\n";
		else
			std::cout << "Miss, loser.\n";
		/*
		switch (move)
		{
		case 1:
			move++;
			break;
		case 2:
			game.shootPiece();
			if (game.ifShot)
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
			move--;
			break;
		}*/

		changePlayer();
		checkWin();
		switch(currState)
		{
		case BBGameState::P1_WIN:
			std::cout << "Player 1 wins!\n";
			break;
		case BBGameState::P2_WIN:
			std::cout << "Player 2 wins!\n";
			break;
		case BBGameState::TIE:
			std::cout << "Tie!\n";
			break;
		default:
			continue;
		}
		currState = BBGameState::END;
	}
	std::cout << "\nGame Over!" << std::endl;
	system("pause");
}
