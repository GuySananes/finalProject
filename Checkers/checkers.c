#include "checkers.h"

//general game functions

void initGame(Board board) {

	USint i, j; //i - row index, j - col index

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
	USint i, j;
	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

//Q1
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {
	SingleSourceMovesTree* ssmTree = makeEmptyTree();
	//if the square is empty - return NULL
	if (board[src->col][src->row] == EMPTY_SQUARE)
		return NULL;
	//create a new Tree
	ssmTree->source = createSSMTreeNode(board, src, NO_CAPTURES, NULL, NULL);
	//build a right sub ssmTree
	USint rightMoveType = findMoveType(board, ssmTree->source->pos, RIGHT);
	buildssmSubTree(board, ssmTree->source, rightMoveType, RIGHT);
	//build a Left sub ssmTree
	USint leftMoveType = findMoveType(board, ssmTree->source->pos, LEFT);
	buildssmSubTree(board, ssmTree->source, leftMoveType, LEFT); 
	
	return ssmTree;
}

/************************
* Input: board, source node and player's data
* Output: return a sub ssmTree by pointer
* Function operation: the function create a tree using recursive call
************************/
void FindSingleSourceMovesHelper(Board board, SingleSourceMovesTreeNode* src, USint player) {
	
	USint leftPos = findMoveType(board, src->pos, LEFT);
	USint rightPos = findMoveType(board, src->pos, RIGHT);
	USint captures = 0;

	checkersPos* nextPos;
	//allocate memory for possition
	nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocaiton(nextPos);

	if (leftPos != CAPTURE && rightPos != CAPTURE) {
		return;
	}

	if (leftPos == CAPTURE) {
		captures++;
		//define the next possition
		nextPos->col = src->pos->col + CAPTURE * player;
		nextPos->row = src->pos->row + CAPTURE * player;
		//create node
		SingleSourceMovesTreeNode* subTreeSource = createSSMTreeNode(board, nextPos, captures, NULL, NULL);
		//define the next move
		src->nextMoves[LEFT] = subTreeSource;
		//create a sub tree
		FindSingleSourceMovesHelper(board, subTreeSource, player);
	}

	if (rightPos == CAPTURE) {
		captures++;
		//define the next possition
		nextPos->col = src->pos->col + CAPTURE * player;
		nextPos->row = src->pos->row + OPPOSITE_DIRECTION * CAPTURE * player;
		//create node
		SingleSourceMovesTreeNode* subTreeSource = createSSMTreeNode(board, nextPos, captures, NULL, NULL);
		//define the next move
		src->nextMoves[RIGHT] = subTreeSource;
		//create a sub tree
		FindSingleSourceMovesHelper(board, subTreeSource, player);
	}
	
}

/************************
* Input: board, current node, next move information (no move, step or capture), direction(left or right)
* Output: return a sub ssmTree by pointer
* Function operation: the function create sub tree using a helper function to the next move if needed
************************/
void buildssmSubTree(Board board, SingleSourceMovesTreeNode* src, USint nextMove, USint dir) {
	
	USint dirIndex = dir; //define diraction index in nextMove array
	USint player = WHICH_PLAYER(board[src->pos->col][src->pos->row]); //define the player
	USint captures = NO_CAPTURES;

	checkersPos* nextPos;
	//allocate memory for possition
	nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocaiton(nextPos);
	
	//set diraction for calculate square, right -> (-1), left -> 1
	dir = SET_DIR(dir);

	if (nextMove == STEP) {
		//define the next possition 
		nextPos->col = src->pos->col +  player;
		nextPos->row = src->pos->row + dir * player;
		//define the right node to be the next step right
		src->nextMoves[dirIndex] = createSSMTreeNode(board, nextPos, NO_CAPTURES, NULL, NULL);
	}

	else if (nextMove == CAPTURE) {
		captures++;
		//define the next possition
		nextPos->col = src->pos->col + CAPTURE * player;
		nextPos->row = src->pos->row + CAPTURE * dir * player;
		SingleSourceMovesTreeNode* subTreeSource = createSSMTreeNode(board, nextPos, captures, NULL, NULL);
		//define the next move
		src->nextMoves[dirIndex] = subTreeSource;
		//create a sub tree
		FindSingleSourceMovesHelper(board, subTreeSource, player);
	}

	else {
		src->nextMoves[dirIndex] = NULL;
		free(nextPos);
	}
}

/************************
* Input: board, current position and direction(left or right)
* Output: an Unsigned short int of the possible move type (no move, step or capture)
* Function operation: the function checks which of the next moves right is avalible
************************/
USint findMoveType(Board board, checkersPos* pos, USint dir) {
	
	USint player = WHICH_PLAYER(board[pos->col][pos->row]);
	//set diraction for calculate square, right -> (-1), left -> 1
	dir = SET_DIR(dir);
	
	//check if next step is in board
	if (pos->col + player >= BOARD_SIZE || pos->row + player * dir >= BOARD_SIZE || pos->col + player < 0 || pos->row + player * dir < 0) {
		return NO_MOVES;
	}
	//check if next step is available
	else if (board[pos->col + player][pos->row + player * dir] == EMPTY_SQUARE) {
		return STEP;
	}
	//check if next capture is in board
	else if (pos->col + CAPTURE * player >= BOARD_SIZE || pos->row + CAPTURE * player * dir >= BOARD_SIZE || pos->col + CAPTURE * player < 0 || pos->row + CAPTURE * player * dir < 0) {
		return NO_MOVES;
	}
	//if there is opponent in the next pos -> check if the square is empty
	else if (WHICH_PLAYER(board[pos->col + player][pos->row + player * dir]) != player) {
		if (board[pos->col +CAPTURE * player][pos->row + CAPTURE * player * dir] == EMPTY_SQUARE) {
			return CAPTURE;
		}
	}
	
	return NO_MOVES;

}

//etc

void checkAllocaiton(void* p) {
	if (p == NULL) {
		printf("MEMORY ALLOCATION FAILED!\n");
		exit(1);
	}
}

//insert detail to the new node
void copyBoard(Board dest, Board source) {
	USint i, j; //i - row index, j - col index

	for (i = 0; i < BOARD_SIZE; i++) {
		for (j = 0; j < BOARD_SIZE; j++) {
			dest[i][j] = source[i][j];
		}
	}
}