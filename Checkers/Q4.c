#include "checkers.h"

//Q3
/************************************************************************************************/

/************************
* Input: board and the current player
* Output: void
* Function operation: the function decides what is the optimal move for the current player given a current board
* the optimal move is dtermined by the "rule of choice"
* the function prints the updated board the move that was played and by which player.
************************/
void Turn(Board board, Player player) {

	multipleSourceMovesList* multipleMovesLst = FindAllPossibleMoves(board, player);
	SingleSourceMovesList* optimal_move_lst = NULL;

	if (multipleMovesLst == NULL)
		return;
	
	optimal_move_lst = getOptimalMove(board, player, multipleMovesLst);

	updateBoard(board, player, optimal_move_lst);
	printf("%c's turn:\n", player);
	printf("%c%c->%c%c\n", (optimal_move_lst->head->position->row + 'A'), (optimal_move_lst->head->position->col + '1'),
		(optimal_move_lst->tail->position->row + 'A'), (optimal_move_lst->tail->position->col + '1'));
	printBoard(board);
}

/************************
* Input: board and the current player
* Output: void
* Function operation: the function chooses the optimal move.
* optimal move will be a move with the highest number of captures
* if the number of captures is the same for more than one position of the player,
* or if there are no captures at all, the optimal move will be
* for T: the move from the highest row and col, for B: the move from the lowest row and col
************************/
SingleSourceMovesList* getOptimalMove(Board board, Player player, multipleSourceMovesList* multipleMovesLst) {

	multipleSourceMovesListCell* max_cell = NULL;
	multipleSourceMovesListCell* cur_cell = NULL;
	unsigned short int max_captures = NO_CAPTURES;
	Sint player_sign = WHICH_PLAYER(player);

	max_cell = cur_cell = multipleMovesLst->head;

	while (cur_cell != NULL) {

		if (cur_cell->single_source_moves_list->tail->captures > max_captures) {

			max_captures = cur_cell->single_source_moves_list->tail->captures;
			max_cell = cur_cell;
		}

		else if (cur_cell->single_source_moves_list->tail->captures == max_captures) {

			if ((player_sign * cur_cell->single_source_moves_list->head->position->row) > player_sign * (max_cell->single_source_moves_list->head->position->row)) {
				max_cell = cur_cell;
			}

			if ((player_sign * cur_cell->single_source_moves_list->head->position->row) == player_sign * (max_cell->single_source_moves_list->head->position->row)) {

				if ((player_sign * cur_cell->single_source_moves_list->head->position->col) > player_sign * (max_cell->single_source_moves_list->head->position->col)) {
					max_cell = cur_cell;
				}
			}
		}
		cur_cell = cur_cell->next;
	}

	if (max_cell != NULL)
		return max_cell->single_source_moves_list;
	else
		return NULL;
}

/************************
* Input: board, the current player and the list of the chosen moves.
* Output: void
* Function operation: the function updates the board: by erasing the player from the current spot to its next spot
and also by erasing the opponents tool.
************************/
void updateBoard(Board board, Player player, SingleSourceMovesList* moves_list) {

	SingleSourceMovesListCell* cur_cell = moves_list->head;
	unsigned short int num_of_cap = moves_list->tail->captures;
	unsigned short int erase_opponent_row = 0, erase_opponent_col = 0;


	if (num_of_cap == NO_CAPTURES) {

		board[moves_list->head->position->row][moves_list->head->position->col] = EMPTY_SQUARE;
		board[moves_list->tail->position->row][moves_list->tail->position->col] = player;
	}

		
	else {

		board[cur_cell->position->row][cur_cell->position->col] = EMPTY_SQUARE;

		while (cur_cell->next != NULL) {

			erase_opponent_row = GET_AVG_POS(cur_cell->next->position->row, cur_cell->position->row);
			erase_opponent_col = GET_AVG_POS(cur_cell->next->position->col, cur_cell->position->col);

			board[erase_opponent_row][erase_opponent_col] = EMPTY_SQUARE;
			cur_cell = cur_cell->next;
		}

		board[moves_list->tail->position->row][moves_list->tail->position->col] = player;
	}
}

