#include "checkers.h"

//general game functions
/************************************************************************************************/


void initGame(Board board) {

	Sint i, j; //i - row index, j - col index

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (i < D) {
				if (IS_GRAY_SQUARE(i, j))
					board[i][j] = PLAYER_1;
				else
					board[i][j] = WHITE_SQUARE;
			}				
			else if (i > E) {
				if (IS_GRAY_SQUARE(i, j))
					board[i][j] = PLAYER_2;
				else
					board[i][j] = WHITE_SQUARE;
			}
			else{
				if (IS_GRAY_SQUARE(i, j))
					board[i][j] = EMPTY_SQUARE;
				else
					board[i][j] = WHITE_SQUARE;
			}
		}
	}

}


void printBoard(Board board) {
	Sint i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

//Q3
/************************************************************************************************/


//etc

void copyBoard(Board dest, Board source) {
	Sint i, j; //i - row index, j - col index

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			dest[i][j] = source[i][j];
		}
	}
}