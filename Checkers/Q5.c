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
}

void gamePlayLoop(Board board, Player player) {

	while (!isGameOver(board, player)) {
		
		//play the optimal move for the player
		Turn(board, player);

		player = SWITCH_PLAYERS(player);
	}
	player = SWITCH_PLAYERS(player);
	printStat(board, player);

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

void printStat(Board board, Player player) {

	printf("%c wins!\n", player);

	if (player == PLAYER_1)
		printf("%c performed %d moves.\n", player, COUNT_MOVES_1);
	else 
		printf("%c performed %d moves.\n", player, COUNT_MOVES_2);
	
	if (COUNT_CAP_1 > COUNT_CAP_2)
		printf("%c performed the highest number of captures in a single move - %d\n", PLAYER_1, COUNT_CAP_1);
	else
		printf("%c performed the highest number of captures in a single move - %d\n", PLAYER_2, COUNT_CAP_2);
		
}