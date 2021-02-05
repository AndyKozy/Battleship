#include "Battleship.h"

void PrintBoard(const std::vector<int>& board, int boardSize)
{
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			for (int k = 0; k < boardSize; k++)
			{
				std::cout << board[i + j * boardSize + k * boardSize * boardSize] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
}


int Battleship(int size)
{
	static int boardSize = 0;
	boardSize = size;
	//roll, pitch, yaw
	int shotx, shoty, shotz; 
	int move = 1;
	//std::cout << "Desired Board Size: ";
	//std::cin >> boardSize;
	
	std::vector<int> board (pow(boardSize,3),0);


	while (0 == 0)
	{
		std::cout << "Where would you (" << move << ") like to shoot: ";
		switch (move)
		{
		case 1:
			move++;
			break;
		case 2:
			move--;
			break;
		}

		std::cin >> shotx;
		std::cin >> shoty;
		std::cin >> shotz;
		board[shotz + shoty * boardSize + shotx * boardSize * boardSize] = -2;
		PrintBoard(board, boardSize);
	}
}


/*
Board Positions:
 3:Shared Ship
 2:Player 2 Ship
 1:Player 1 Ship
 0:Empty Space
-1:Miss
-2:Hit
*/

/*
Order of making things:
1.Board :D
2.Shooting
3.Placing Pieces
4.Graphics
5.Seperating
6.Network
*/