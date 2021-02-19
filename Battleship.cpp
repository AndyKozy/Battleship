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
using coord_type = Battleship3D::coord_type;


void Battleship3D::makeBoard()
{
	boardSize = 8;
	gameState = 0;
	ifShot = 0;
	for (size_t i = 0; i < pow(boardSize, 2) * boardDepth; i++)
	{
		playerBoard1.push_back(' ');
		playerBoard2.push_back('#');
	}
	std::cout << "Board size is: ";
	for (int i = 0; i < 2; ++i)
		std::cout << boardSize << 'x';
	std::cout << boardDepth << std::endl;
}

std::string Battleship3D::getPieceName()
{
	std::string gamePiece;
	std::getline(std::cin, gamePiece);														//grab the string with getline()
	std::transform(gamePiece.begin(), gamePiece.end(), gamePiece.begin(), std::tolower);	//turn all chars to lowercase
	gamePiece.erase(remove(gamePiece.begin(), gamePiece.end(), ' '), gamePiece.end());		//remove whitespace
	return gamePiece;
}


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
	coordinates = std::make_tuple(_x, _y, _z);
}

void Battleship3D::checkWin()
{
	bool gameEnd1 = true;
	bool gameEnd2 = true;
	for (auto& n : playerBoard1)
	{
		if (n == '#')
			gameEnd1 = false;
	}
	for (auto& n : playerBoard2)
	{
		if (n == '#')
			gameEnd2 = false;
	}

	if (!gameEnd1 && gameEnd2)
		gameState = 1;
	else if (gameEnd1 && !gameEnd2)
		gameState = 2;
	else if (gameEnd1 && gameEnd2)
		gameState = 3;
	else 
		gameState = 0;
}

void Battleship3D::checkShot(board_type& firstBoard, board_type& secondBoard, size_t& position)
{
	if (firstBoard[position] == BBMarkerType::PIECE)
	{
		firstBoard[position] = BBMarkerType::HIT;
		ifShot = true;
	}
	else
		playerBoard1[position] = BBMarkerType::MISS;

	if (playerBoard2[position] == BBMarkerType::PIECE)
	{
		playerBoard1[position] = BBMarkerType::HIT;
		ifShot = 1;
	}
	playerBoard2[position] = BBMarkerType::SHOT;
}

void Battleship3D::shootPiece()
{
	ifShot = false;
	size_t shotCoords;

	//Determining if shot has been made
	while (true)
	{
		setCoordinates();
		//std::tie(_x, _y, _z) = coordinates;
		shotCoords = (_x + boardSize * _y + pow(boardSize, 2) * _z);

		if (playerBoard1[shotCoords] != BBMarkerType::PIECE && 
			playerBoard1[shotCoords] != BBMarkerType::EMPTY)
			std::cout << "Shot already made. Enter new shot: ";
		else
			break;
	}

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
	
} //Needs fixing due to duplicate code //Minor solution. see checkShot()

void Battleship3D::printTopLabel(size_t &layer)
{
	whitespace = 1;
	char letter = 'A';

	//TOP LABELS make into a function?
	std::cout << "LAYER " << layer << std::endl;
	printSpaceShift(whitespace);
	for (letter; letter < (boardSize + 'A'); ++letter)
		std::cout << "  " << letter << " ";
	std::cout << "\n";
}

void Battleship3D::printDiagSideLabel(size_t& row)
{
	printSpaceShift(whitespace);
	printBorder();
	std::cout << "\n";
	whitespace--;
	printSpaceShift(whitespace);
	std::cout << row << " ";
}

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
				std::cout << "\\ " << currBoard[x + y * boardSize + z * pow(boardSize, 2)] << ' ';
			}
			std::cout << "\\" << std::endl;
			
			whitespace += 3;
		}
		printSpaceShift(whitespace);
		printBorder();
		std::cout << std::endl << std::endl;
	}
}


/*
void Battleship(int size)
{
	//Is currently being used by Player 1
	//Maybe use copy constructor to make one for each player?
	//key --> gamePiece(name|length) & quantity
	PcsMAPTYPE inventory{ {"carrier",		{"Carrier",		5,	1}},
							{"battleship",	{"Battleship",	4,	2}},
							{"destroyer",	{"Destroyer",	3,	1}},
							{"submarine",	{"Submarine",	3,	2}},
							{"patrolboat",	{"Patrol Boat",	2,	4}} };
*/

void runGame()
{
	int move;
	Battleship3D game;
	game.numOfPlayers = 2;
	game.makeBoard();
	game.currPlayer = 1;

	while (0 == 0)
	{
		move = game.currPlayer;
		switch (move)
		{
		case 1:
			game.currBoard = game.playerBoard1;
			break;
		case 2:
			game.currBoard = game.playerBoard2;
			break;
		}
		game.printBoard();

		//A switch statement, cuz I know you don't like 'em >:D
		std::cout << "Player " << move << "\n";
		std::cout << "Where would you (" << move << ") like to shoot: [x y z] ";
		switch (move)
		{
		case 1:
			game.shootPiece();
			if (game.ifShot)
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
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
		}

		//Battleship.checkWin();
		if (game.gameState == 1)
		{
			std::cout << "Player 1 wins!\n";
			break;
		}
		if (game.gameState == 2)
		{
			std::cout << "Player 2 wins!\n";
			break;
		}
		if (game.gameState == 3)
		{
			std::cout << "Tie!\n";
			break;
		}

		game.changePlayer();

		//getline(std::cin, input);
		//std::stringstream sstream(input);
		//sstream >> shotX >> shotY >> shotZ;
		//TODO: Make a translation of battleship notation (A3, B6) to coordinates..?
		//std::tie(shotX, shotY, shotZ) = getIntCoord();
		//board[shotX + boardSize * shotY + pow(boardSize,2) * shotZ] = -2;
		//board[shotZ + shotY * DEPTH + shotX * boardSize * DEPTH] = -2;

	}
	system("pause");
}