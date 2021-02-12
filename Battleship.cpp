#include "Battleship.h"

///GLOBAL VARIABLES
const int DEPTH = 3; //z axis
static int boardSize = 0;

void Battleship(int size)
{
	//Is currently being used by Player 1
	//Maybe use copy constructor to make one for each player?
	//key --> gamePiece(name|length) & quantity
	PcsMAPTYPE inventory{	{"carrier",		{"Carrier",		5,	0}},
							{"battleship",	{"Battleship",	4,	0}},
							{"destroyer",	{"Destroyer",	3,	0}},
							{"submarine",	{"Submarine",	3,	0}},
							{"patrolboat",	{"Patrol Boat",	2,	0}}};

	//Don't know if this will be used outside of	 PlacePieces()
	//if not used for Battleship(), move these 3 lines to ^^^^
	int totalPieces = 0;
	for (const auto& [key, item] : inventory)
		totalPieces += item.pieceAmount;
	//std::cout << totalPieces;

	boardSize = size; //used for Catch2
	//std::string input; //was used for getting coords. Now handled by getIntCoords() (see below)

	int shotX = 0, //left/right
		shotY = 0, //forward/back
		shotZ = 0; //up/down
	int move = 1;
	int gameState = 0;
	//std::cout << "Desired Board Size: ";
	//std::cin >> boardSize;
	

	BoardTYPE board (pow(boardSize, 2)*DEPTH,0); //1D array as 3D space
	BoardTYPE board2(pow(boardSize, 2) * DEPTH, 0); //temp
	board[16] = 1;
	board2[15] = 1;

	std::cout << "Board size is: ";
	for (int i = 0; i < 2; ++i)
		std::cout << boardSize << "x";
	std::cout << DEPTH << std::endl;
	system("pause"); //REMOVE IF GRAPHICS EVER GET IMPLEMENTED

	//PlacePieces(board, boardSize, inventory, totalPieces);
	
	while (0 == 0)
	{
		switch (move)
		{
		case 1:
			PrintBoard(board, boardSize);
			break;
		case 2:
			PrintBoard(board2, boardSize);
			break;
		}
		
		gameState = checkWin(board, board2);
		if (gameState == 1)
		{
			std::cout << "Player 1 wins!";
			break;
		}
		if (gameState == 2)
		{
			std::cout << "Player 2 wins!";
			break;
		}
		if (gameState == 3)
		{
			std::cout << "Tie!";
			break;
		}

		//A switch statement, cuz I know you don't like 'em >:D
		std::cout << "Player " << move << "\n";
		std::cout << "Where would you (" << move << ") like to shoot: [x y z] ";
		switch (move)
		{
		case 1:
			if (shootPiece(board, board2))
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
			move++;
			system("pause");
			break;
		case 2:
			if (shootPiece(board2, board))
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
			move--;
			system("pause");
			break;
		}


		//getline(std::cin, input);
		//std::stringstream sstream(input);
		//sstream >> shotX >> shotY >> shotZ;
		//TODO: Make a translation of battleship notation (A3, B6) to coordinates..?
		//std::tie(shotX, shotY, shotZ) = getIntCoord();
		//board[shotX + boardSize * shotY + pow(boardSize,2) * shotZ] = -2;
		//board[shotZ + shotY * DEPTH + shotX * boardSize * DEPTH] = -2;

	}
}

void PrintBoard(const std::vector<int>& board, int boardSize)
{
	system("cls");
	//Maybe use iterators?
	for (size_t z = 0; z < DEPTH; z++)
	{
		for (size_t y = 0; y < boardSize; y++)
		{
			for (size_t x = 0; x < boardSize; x++)
			{
				std::cout << board[x + y * boardSize + z * pow(boardSize,2)] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}

std::string getStrInput()
{
	std::string str = "";
	std::getline(std::cin, str);										//grab the string with getline()
	std::transform(str.begin(), str.end(), str.begin(), std::tolower);	//turn all chars to lowercase
	str.erase(remove(str.begin(), str.end(), ' '), str.end());			//remove whitespace

	return str;
}

//NEEDS ERROR HANDLING
//getIntCoord
/*
Uses stringstream to grab 3 ints
Returns a tuple
Use std::tie to assign the values to 3 variables.
*/
std::tuple<int,int,int> getIntCoord()
{
	//Andrew, needs some tweaking but this is the general implementation
	//only reads with a ' ' (space) delimiter...
	size_t x, y, z;
	do
	{
		std::string temp = "";
		std::getline(std::cin, temp);
		std::stringstream sstream(temp);
		sstream >> x >> y >> z;
		if (x >= boardSize || y >= boardSize || z >= DEPTH)
			std::cout << "Invalid Coordinates. Enter new ones, dummy: " << std::endl;
		else
			break;
	} while (true);

	return std::make_tuple(x, y, z);
}

/*
void PlacePieces(BoardTYPE& board, const int& boardSize, PcsMAPTYPE& inv, int totPieces)
{
	//cout formatting stuff
	const char delim = ' ';
	const int nameWid = 12;
	const int quantWid = 5;

	//TODO: some checking for bad input
	int xCoord = -1;
	int yCoord = -1;
	int zCoord = -1;
	int piecesPlaced = 0;

	
	while (piecesPlaced < totPieces)
	{
		system("cls"); //Remove this(?) if graphics get put in
		PrintBoard(board, boardSize);
		std::cout << "Pick a game piece: " << std::endl;

		for (const auto& [name, piece] : inv)
		{
			//format a table output	//FIX ME
			std::cout << std::left << std::setw(nameWid) << name << " {" << piece.pieceAmount << "} | ";
		}
		std::cout << std::endl;

		auto& itr = inv.find(getStrInput()); //grab the string input and search through the inventory
		if (itr != inv.end())
		{
			//for readability's sake
			auto &quantity =	itr->second.pieceAmount; //quantity
			auto &piece =		itr->second.name;  //gamePiece
			auto &pieceLength = itr->second.length;
			if (quantity > 0)
			{
				std::cout << "[SELECTION]: " << piece << " " << pieceLength << "\n"
					<< "[REMAINING]: " << quantity << std::endl;
				//TODO: prompt comfirmation of selected piece b4 asking where to place
				std::cout << "Where would you like to place your ship? [x y z]: ";

				std::tie(xCoord, yCoord, zCoord) = getIntCoord();
				//magic stuff, place the piece
				//TODO: Ask which orientation (vertical|horizontal)
				//TODO: Display placement of ship, ask for confirmation b4 modifying the board.
				//TODO: Check board if a user's piece overlaps the selection,
				//		Restart coord placement prompt

				//SUGGESTION:
				// Odd-sized pieces are centered corresponding to the placement coord, sorta a pivot
				// A size 4 piece follows the same placement rules as a size 3 piece where,
				// the non-overlapping tail-end ALWAYS points to the west/south.
				// A size 2 piece is similar in that the tail-end will ALWAYS point to the west/south
				// Pieces placed at the edges or corners will "bump back" this "pivot point" (plcmntCoord)
				// so that the code won't break :')
				
			}
			else
			{
				std::cout << "You've already placed these pieces." << std::endl;
				system("pause"); //REMOVE WHEN GRAPHICS ARE USED
				continue;
			}
			//if successful, reduce quantity and ++piecesPlaced
			quantity--;
			++piecesPlaced;
		}
		else
			std::cout << "Not a valid game piece. Try again." << std::endl;
		system("pause"); //REMOVE LATER FOR GRAPHICS/PROPER GAME LOOP
	}
}
*/

bool shootPiece(BoardTYPE& playerBoard, BoardTYPE& enemyBoard) {
	size_t x, y, z;
	bool ifShot = 0;
	while (true)
	{
		std::tie(x, y, z) = getIntCoord();
		if (playerBoard[x + boardSize * y + pow(boardSize, 2) * z] != 1 && playerBoard[x + boardSize * y + pow(boardSize, 2) * z] != 0)
		{
			std::cout << "Shot already made. Enter new shot: ";
		}
		else
			break;
	}
	

	if (playerBoard[x + boardSize * y + pow(boardSize, 2) * z] == 1)
	{
		playerBoard[x + boardSize * y + pow(boardSize, 2) * z] = -2;
		ifShot = 1;
	}
	else
		playerBoard[x + boardSize * y + pow(boardSize, 2) * z] = -1;


	if (enemyBoard[x + boardSize * y + pow(boardSize, 2) * z] == 1)
	{
		playerBoard[x + boardSize * y + pow(boardSize, 2) * z] = -2;
		ifShot = 1;
	}
	enemyBoard[x + boardSize * y + pow(boardSize, 2) * z] = -3;


	return ifShot;
}

int checkWin(BoardTYPE& board1, BoardTYPE& board2) {
	bool gameEnd1 = true;
	bool gameEnd2 = true;
	for (auto& n : board1)
	{
		if (n == 1)
			gameEnd1 = false;
	}
	for (auto& n : board2)
	{
		if (n == 1)
			gameEnd2 = false;
	}

	if (!gameEnd1 && gameEnd2)
		return 1;
	if (gameEnd1 && !gameEnd2)
		return 2;
	if (gameEnd1 && gameEnd2)
		return 3;
	return 0;
	
}

/*
Board Positions:
 1:Player Ship
 0:Empty Space
-1:Miss
-2:Hit
-3:Enemy Shot
*/

/*
Order of making things:
1.Board :D
2.Shooting :D
3.Checking a win :D
4.Placing Pieces
5.Graphics
6.Seperating
7.Network
*/