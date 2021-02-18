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

void BoardFactory::diagonalShift(int printShift)
{
	for (int i = 0; i < printShift; ++i)
		std::cout << " ";
}

void BoardFactory::borderPrint()
{
	for (int i = 0; i < boardSize; ++i)
		std::cout << "+---";
	std::cout << "+";
}

void BoardFactory::getPieceInput()
{
	std::getline(std::cin, gamePiece);														//grab the string with getline()
	std::transform(gamePiece.begin(), gamePiece.end(), gamePiece.begin(), std::tolower);	//turn all chars to lowercase
	gamePiece.erase(remove(gamePiece.begin(), gamePiece.end(), ' '), gamePiece.end());		//remove whitespace	
}

void BoardFactory::getIntCord()
{
	size_t x, y, z;
	while (true)
	{
		std::string temp = "";
		std::getline(std::cin, temp);
		std::stringstream sstream(temp);
		sstream >> x >> y >> z;
		if (x >= boardSize || y >= boardSize || z >= boardDepth)
			std::cout << "Invalid Coordinates: " << std::endl;
		else
			break;
	}
	cordinate = std::make_tuple(x, y, z);
}

void BoardFactory::checkWin()
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

void BoardFactory::shootPiece()
{
	size_t x, y, z;
	ifShot = 0;

	//Determining if shot has been made
	while (true)
	{
		getIntCord();
		std::tie(x, y, z) = cordinate;
		if (playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] != '#' && playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] != ' ')
		{
			std::cout << "Shot already made. Enter new shot: ";
		}
		else
			break;
	}

	if (player == 1)
	{
		if (playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] == '#')
		{
			playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] = 'X';
			ifShot = 1;
		}
		else
			playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] = '_';

		if (playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] == '#')
		{
			playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] = 'X';
			ifShot = 1;
		}
		playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] = '/';
	}
	else
	{
		if (playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] == '#')
		{
			playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] = 'X';
			ifShot = 1;
		}
		else
			playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] = '_';

		if (playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] == '#')
		{
			playerBoard2[x + boardSize * y + pow(boardSize, 2) * z] = 'X';
			ifShot = 1;
		}
		playerBoard1[x + boardSize * y + pow(boardSize, 2) * z] = '/';
	}
	
} //Needs fixing due to duplicate code

void BoardFactory::printBoard(const std::vector<char> board)
{
	for (size_t z = 0; z < boardDepth; z++)
	{
		int printShift = 1;
		char letter = 'A';

		std::cout << "LAYER " << z << std::endl;
		diagonalShift(printShift);
		for (letter; letter < (boardSize + 'A'); ++letter)
			std::cout << "  " << letter << " ";
		std::cout << "\n";

		for (size_t y = 0; y < boardSize; y++)
		{
			//print stuff
			diagonalShift(printShift);
			borderPrint();
			std::cout << "\n";
			printShift--;
			diagonalShift(printShift);
			std::cout << y << " ";

			for (size_t x = 0; x < boardSize; x++)
			{
				//a switch within a switch statement, because why not? >:D //LMAO YOU THOUGHT YOU COULD SWITCH ME NONONO I MADE THE ENTIRE SWITCH STATEMENT 1 LINE MUAHAHAHAHAHAH
				//touché, but the spacing was off >:P
				std::cout << "\\ " << board[x + y * boardSize + z * pow(boardSize, 2)] << ' ';
			}
			std::cout << "\\" << std::endl;
			printShift += 3;
		}
		diagonalShift(printShift);
		borderPrint();
		std::cout << std::endl << std::endl;
	}
}

BoardFactory::BoardFactory()
{
	boardSize = 8;
	boardDepth = 3;
	player = 1;
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

void BoardFactory::changePlayer()
{
	if (player == 1)
		player = 2;
	else
		player = 1;
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

void gameRun()
{
	int move;
	BoardFactory Battleship;
	while (0 == 0)
	{
		move = Battleship.player;
		switch (move)
		{
		case 1:
			Battleship.printBoard(Battleship.playerBoard1);
			break;
		case 2:
			Battleship.printBoard(Battleship.playerBoard2);
			break;
		}

		//A switch statement, cuz I know you don't like 'em >:D
		std::cout << "Player " << move << "\n";
		std::cout << "Where would you (" << move << ") like to shoot: [x y z] ";
		switch (move)
		{
		case 1:
			Battleship.shootPiece();
			if (Battleship.ifShot)
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
			move++;
			break;
		case 2:
			Battleship.shootPiece();
			if (Battleship.ifShot)
				std::cout << "Hit!\n";
			else
				std::cout << "Miss, loser.\n";
			move--;
			break;
		}

		//Battleship.checkWin();
		if (Battleship.gameState == 1)
		{
			std::cout << "Player 1 wins!\n";
			break;
		}
		if (Battleship.gameState == 2)
		{
			std::cout << "Player 2 wins!\n";
			break;
		}
		if (Battleship.gameState == 3)
		{
			std::cout << "Tie!\n";
			break;
		}

		Battleship.changePlayer();

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