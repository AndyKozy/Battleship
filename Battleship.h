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

void gameRun();

class BoardFactory {
public:
	BoardFactory();
	void getIntCord();
	void printBoard(const std::vector<char> board);
	//void placePieces();
	void shootPiece();
	void diagonalShift(int printShift);
	void borderPrint();
	void getPieceInput();
	void checkWin();
	void changePlayer();
	std::vector<char> playerBoard1;
	std::vector<char> playerBoard2;
	bool ifShot;
	int gameState;
	int player;
private:
	int boardSize;
	int boardDepth;
	std::string gamePiece;
	std::tuple<int, int, int> cordinate;
	
};