#include "checkers.h"

//Trees function

SingleSourceMovesTree* makeEmptyTree() {

	SingleSourceMovesTree* tree;
	tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
	checkAllocaiton(tree);
	return tree;
}

SingleSourceMovesTreeNode* createSSMTreeNode(Board board, checkersPos* pos, unsigned short totalCaptures, SingleSourceMovesTreeNode* LeftnextMove, SingleSourceMovesTreeNode* RightnextMove) {

	SingleSourceMovesTreeNode* newTreeNode;
	checkersPos* newPos;
	
	//allocate memory for the new node
	newTreeNode = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAllocaiton(newTreeNode);
	
	//insert detail to the new node
	copyBoard(newTreeNode->board, board);
	//allocate memory for the node possition
	newPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAllocaiton(newPos);
	*newPos = *pos;
	newTreeNode->pos = newPos;
	newTreeNode->total_captures_so_far = totalCaptures;
	newTreeNode->nextMoves[LEFT] = LeftnextMove;
	newTreeNode->nextMoves[RIGHT] = RightnextMove;

	return newTreeNode;

}