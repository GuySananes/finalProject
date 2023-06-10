#include "checkers.h"

//Q1
/************************************************************************************************/

/************************
* Input: board and source square
* Output: return a tree of all possible moves from that square
* Function operation: the function create a tree using helper fucntion
************************/
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) {

	//create new tree
	SingleSourceMovesTree* ssmTree = makeEmptyTree();

	//if the square is empty - return NULL
	if (board[src->row][src->col] == EMPTY_SQUARE)
		return NULL;

	//create a new Tree Node
	ssmTree->source = createSSMTreeNode(board, src, NO_CAPTURES, NULL, NULL);

	//build a Left sub ssmTree
	Sint leftMoveType = findMoveType(board, ssmTree->source->pos, LEFT);
	buildssmSubTree(board, ssmTree->source, leftMoveType, LEFT);

	//build a right sub ssmTree
	Sint rightMoveType = findMoveType(board, ssmTree->source->pos, RIGHT);
	buildssmSubTree(board, ssmTree->source, rightMoveType, RIGHT);

	return ssmTree;
}

/************************
* Input: board, source node and player's data
* Output: return a sub ssmTree by pointer
* Function operation: the function create a tree using recursive call
************************/
void FindSingleSourceMovesHelper(Board board, SingleSourceMovesTreeNode* src, Sint player) {

	//find left and right possition
	Sint leftPos = findMoveType(board, src->pos, LEFT);
	
	Sint rightPos = findMoveType(board, src->pos, RIGHT);
	Sint captures = src->total_captures_so_far;

	//create a sub tree recursively
	if (leftPos == CAPTURE) {
		addNextCaptureNode(board, src, player, captures, LEFT);
		FindSingleSourceMovesHelper(board, src->nextMoves[LEFT], player);
	}
	if (rightPos == CAPTURE) {
		addNextCaptureNode(board, src, player, captures, RIGHT);
		FindSingleSourceMovesHelper(board, src->nextMoves[RIGHT], player);
	}
	
	return;
}

/************************
* Input: board, current node, next move information (no move, step or capture), direction(left or right)
* Output: return a sub ssmTree by pointer
* Function operation: the function create sub tree using a helper function to the next move if needed
************************/
void buildssmSubTree(Board board, SingleSourceMovesTreeNode* src, Sint nextMoveType, Sint dir) {

	Sint dirIndex = dir; //define diraction index in nextMove array
	Sint playerSign = WHICH_PLAYER(board[src->pos->row][src->pos->col]); //define the player
	checkersPos* nextPos;

	//allocate memory for possition
	nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	//if (nextPos == NULL) { exit(1); }
	CHECK_ALLOCATION(nextPos);

	//set diraction for calculate square, right -> (-1), left -> 1
	dir = SET_DIR(dir);

	//build the sub tree by the move type
	if (nextMoveType == STEP) {
		//define the next possition 
		nextPos->col = src->pos->col + dir * playerSign;
		nextPos->row = src->pos->row + playerSign;
		//define the right node to be the next step right
		src->nextMoves[dirIndex] = createSSMTreeNode(board, nextPos, NO_CAPTURES, NULL, NULL);
	}
	else if (nextMoveType == CAPTURE) {
		addNextCaptureNode(board, src, playerSign, NO_CAPTURES, dirIndex);
		FindSingleSourceMovesHelper(board, src->nextMoves[dirIndex], playerSign);
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
Sint findMoveType(Board board, checkersPos* pos, Sint dir) {

	//define the player as calulation value. 1 -> player 1, -1 -> player 2
	Sint player = WHICH_PLAYER(board[pos->row][pos->col]);
	//set diraction for calculate square, right -> (-1), left -> 1
	dir = SET_DIR(dir);
	
	//check if next step is in board
	if (pos->col + player * dir >= BOARD_SIZE || pos->row + player >= BOARD_SIZE || pos->col + player * dir < 0 || pos->row + player < 0) {
		return NO_MOVES;
	}
	
	//check if next step is available
	else if (board[pos->row + player][pos->col + player * dir] == EMPTY_SQUARE) {
		return STEP;
	}
	//check if next capture is in board
	else if (pos->col + CAPTURE * player * dir >= BOARD_SIZE || pos->row + CAPTURE * player >= BOARD_SIZE || pos->col + CAPTURE * player * dir < 0 || pos->row + CAPTURE * player < 0) {
		return NO_MOVES;
	}
	//if there is opponent in the next pos -> check if the square is empty
	else if (WHICH_PLAYER(board[pos->row + player][pos->col + player * dir]) != player) {
		if (board[pos->row + CAPTURE * player][pos->col + CAPTURE * player * dir] == EMPTY_SQUARE) {
			return CAPTURE;
		}
	}

	return NO_MOVES;

}

/************************
* Input: board, source, player, captures, direction
* Output: ssmTree Node assuming the next move is capture
* Function operation: the function allocate possition, create Tree Node and insert it to the tree
************************/
void addNextCaptureNode(Board board, SingleSourceMovesTreeNode* src, Sint player, Sint captures, Sint dir) {

	Sint dirIndex = dir;
	checkersPos* nextPos;

	//allocate memory for possition
	nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	CHECK_ALLOCATION(nextPos);

	//set direction for calculation
	dir = SET_DIR(dir);

	//advance captures
	captures++;

	//define the next possition
	nextPos->col = src->pos->col + CAPTURE * dir * player;
	nextPos->row = src->pos->row + CAPTURE * player;

	//remove oponent from board
	board[src->pos->row][src->pos->col] = EMPTY_SQUARE;
	board[src->pos->row + player][src->pos->col + dir * player] = EMPTY_SQUARE;
	board[nextPos->row][nextPos->col] = PLAYER_TO_CHAR(player);


	//define the next move
	SingleSourceMovesTreeNode* subTreeSource = createSSMTreeNode(board, nextPos, captures, NULL, NULL);
	
	src->nextMoves[dirIndex] = subTreeSource;

}

//SingleSourceMoves tree function

SingleSourceMovesTree* makeEmptyTree() {

	SingleSourceMovesTree* tree;
	tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	CHECK_ALLOCATION(tree);
	return tree;
}

SingleSourceMovesTreeNode* createSSMTreeNode(Board board, checkersPos* pos, unsigned short int totalCaptures, SingleSourceMovesTreeNode* LeftnextMove, SingleSourceMovesTreeNode* RightnextMove) {

	SingleSourceMovesTreeNode* newTreeNode;
	checkersPos* newPos;

	//allocate memory for the new node
	newTreeNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	CHECK_ALLOCATION(newTreeNode);

	//insert detail to the new node
	copyBoard(newTreeNode->board, board);
	//allocate memory for the node possition
	newPos = (checkersPos*)malloc(sizeof(checkersPos));
	CHECK_ALLOCATION(newPos);

	newPos = pos;
	newTreeNode->pos = newPos;
	newTreeNode->total_captures_so_far = totalCaptures;
	newTreeNode->nextMoves[LEFT] = LeftnextMove;
	newTreeNode->nextMoves[RIGHT] = RightnextMove;

	return newTreeNode;

}

void freeSSMTree(SingleSourceMovesTree* tree) {
	freeSSMTreeHelper(tree->source);
	free(tree);
}

void freeSSMTreeHelper(SingleSourceMovesTreeNode* src) {

	if (src == NULL) {
		return;
	}

	freeSSMTreeHelper(src->nextMoves[LEFT]);
	freeSSMTreeHelper(src->nextMoves[RIGHT]);

	free(src->pos);
	free(src);
	return;
}
