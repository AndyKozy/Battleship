#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <array>

#include <cmath>
#include <algorithm>
#include <utility>

struct gamePiece
{
	const std::string name;
	const int length;
	int pieceAmount;
};

using PcKEYTYPE = std::string;
using PcELEMTYPE = gamePiece; //piece w/ quantity
using PcsMAPTYPE = std::map<PcKEYTYPE, PcELEMTYPE>;
using BoardTYPE = std::vector<int>;

std::string getStrInput();

std::tuple<int, int, int> getIntCoord();

void PlacePieces(BoardTYPE& board, const int& boardSize, PcsMAPTYPE& inv, int totPieces);

void PrintBoard(const std::vector<int>&, int);

bool shootPiece(BoardTYPE& playerBoard, BoardTYPE& enemyBoard);

int Battleship(int);
