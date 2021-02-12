#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <string>
#include <map>
#include <unordered_map>

#include <cmath>
#include <algorithm>
#include <utility>

struct gamePiece
{
	const std::string name;
	const int length;
	int amount;
};

using PcKEYTYPE = std::string;
using PcELEMTYPE = gamePiece; //piece w/ quantity
using PcsMAPTYPE = std::map<PcKEYTYPE, PcELEMTYPE>;
using BoardTYPE = std::vector<char>;

std::string getStrInput();

std::tuple<int, int, int> getIntCoord();

void PlacePieces(BoardTYPE& board, const int& boardSize, PcsMAPTYPE& inv, int totPieces);

void PrintBoard(const BoardTYPE& board, int);

bool shootPiece(BoardTYPE& playerBoard, BoardTYPE& enemyBoard);

void Battleship(int);

int checkWin(BoardTYPE& board, BoardTYPE& board1);
