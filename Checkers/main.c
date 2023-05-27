#include "checkers.h"

void main() {
	Board board;
	checkersPos pos;
	pos.col = F;
	pos.row = 2;
	initGame(board);
	printBoard(board);
	FindSingleSourceMoves(board, &pos);
	
}