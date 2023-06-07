#include "checkers.h"

//Q5
/************************************************************************************************/

/************************
* Input: board and starting player
* Output: void
* Function operation: the function prints the moves of each player and the updated board after the move
* at the end of the games the function prints the winner and game statistics.
************************/
void PlayGame(Board board, Player starting_player) {
	printBoard(board);
	gamePlayLoop(board, starting_player);
	//printStat();
}

void gamePlayLoop(Board board, Player player) {

	while (!isGameOver(board, player)) {
		printf("%c's turn:\n", player);

		//play the optimal move for the player
		//Turn(board, player);

		//prints his last move
		//printmove();

		//prints the board after playing the turn
		printBoard(board);

		//		
		player = SWITCH_PLAYERS(player);
	}
}

bool isGameOver(Board board, Player player) {

	unsigned short int i, j, count = 0;

	//checks if player has cheaps
	for (i = 0; i < BOARD_SIZE && count == 0; i++) {
		for (j = i % 2 + 1; j < BOARD_SIZE; j += 2) {
			if (board[i][j] == player)
				count++;
		}		
	}

	if (player == PLAYER_1) {
		for (j = 2; j < BOARD_SIZE; j += 2) {
			if (board[A][j] == PLAYER_2)
				return true;
		}
	}
	else {
		for (j = 0; j < BOARD_SIZE; j += 2) {
			if (board[H][j] == PLAYER_1)
				return true;
		}
	}

	return (!count);

}