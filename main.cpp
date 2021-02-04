#include <iostream>
#include <vector>

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

int main()
{
	int boardSize = 0;
	int shotx, shoty, shotz;
	int move = 1;
	std::cout << "Desired Board Size: ";
	std::cin >> boardSize;
	
	std::vector<int> board (boardSize*boardSize*boardSize,0);

	

	while (0 == 0)
	{
		if (move == 1)
		{
			std::cout << "Where would you (1) like to shoot: ";
			std::cin >> shotx;
			std::cin >> shoty;
			std::cin >> shotz;
			board[shotz + shoty * boardSize + shotx * boardSize * boardSize] = -2;
			PrintBoard(board, boardSize);
			move = 2;
		}
		if (move == 2)
		{
			std::cout << "Where would you (2) like to shoot: ";
			std::cin >> shotx;
			std::cin >> shoty;
			std::cin >> shotz;
			board[shotz + shoty * boardSize + shotx * boardSize * boardSize] = -2;
			PrintBoard(board, boardSize);
			move = 1;
		}
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