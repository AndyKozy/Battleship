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
};

using PcKEYTYPE = std::string;
using PcELEMTYPE = std::pair<gamePiece, int>; //piece w/ quantity
using PcsMAPTYPE = std::map<PcKEYTYPE, PcELEMTYPE>;
using BoardTYPE = std::vector<int>;

std::string getStrInput();

void PlacePieces(BoardTYPE& board, const int& boardSize, PcsMAPTYPE& inv, int totPieces);

void PrintBoard(const std::vector<int>&, int);

int Battleship(int);
