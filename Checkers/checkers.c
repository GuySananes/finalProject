#include "checkers.h"

//general game functions
/************************************************************************************************/


void initGame(Board board) {

	initGameHelper(A, D, PLAYER_1, board);
	initGameHelper(D, F, EMPTY_SQUARE, board);
	initGameHelper(F, BOARD_SIZE, PLAYER_2, board);

}

void initGameHelper(int start, int end, char tool, Board board) {
	int i, j;
	for (i = start; i < end; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			if (IS_GRAY_SQUARE(i, j))
				board[i][j] = tool;
			else
				board[i][j] = WHITE_SQUARE;
		}
	}
}

void printBoard(Board board) {
	Sint i, j;
	PRINT_LINE;
	PRINT_NUMBERS;
	PRINT_LINE;
	for (i = 0; i < BOARD_SIZE; i++) {
		printf("|%c", i + 'A');
		for (j = 0; j < BOARD_SIZE; j++) {
			printf("|%c", board[i][j]);
		}
		printf("|\n");
		PRINT_LINE;
	}
	printf("\n");
}

//etc

void copyBoard(Board dest, Board source) {
	Sint i, j; //i - row index, j - col index

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			dest[i][j] = source[i][j];
		}
	}
}