#include "checkers.h"

void main() {
	Board board;
	checkersPos pos;
	pos.col = F;
	pos.row = 2;
	initGame(board);
	/*board[4][1] = 'T';
	board[1][2] = EMPTY_SQUARE;
	board[2][3] = EMPTY_SQUARE;
	board[2][5] = EMPTY_SQUARE;
	board[4][3] = 'T';*/
	printBoard(board);
	
	FindAllPossibleMoves(board, PLAYER_1);
}