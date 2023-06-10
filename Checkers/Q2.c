#include "checkers.h"

//Q2
/************************************************************************************************/

#define BLOCKED -1

/************************
* Input: moves Tree of a square
* Output: optimal moves list
* Function operation: create the list using helper function
************************/
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree) {
	//TODO!!!!!!!!!!! add validation for tree pointer
	return FindSingleSourceOptimalMoveHelper(moves_tree->source);

}

/************************
* Input: a tree node
* Output: optimal moves list
* Function operation: the function create two optimal lists using a recursive call, choose the optimal list,
* add the node to the list and free the other one
************************/
SingleSourceMovesList* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* src) {

	SingleSourceMovesList* leftList, * rightList;
	Sint capturesRight = BLOCKED, capturesLeft = BLOCKED;

	//break condition - end of the tree -> return empty list
	if (src == NULL) {
		return makeEmptySSMList();
	}

	//recursive call to create to lists
	leftList = FindSingleSourceOptimalMoveHelper(src->nextMoves[LEFT]);
	rightList = FindSingleSourceOptimalMoveHelper(src->nextMoves[RIGHT]);

	//a condition to avoid null
	if (leftList->tail != NULL) {
		capturesLeft = leftList->tail->captures;
	}

	if (rightList->tail != NULL) {
		capturesRight = rightList->tail->captures;
	}

	//insert the node the the optimal list and free the other
	if (capturesLeft >= capturesRight) {
		insertTreeNodeToStartList(src, leftList);
		freeList(rightList);
		return leftList;
	}

	else {
		insertTreeNodeToStartList(src, rightList);
		freeList(leftList);
		return rightList;
	}
}


//SingleSourceMoves list fucntions

SingleSourceMovesList* makeEmptySSMList() {
	SingleSourceMovesList* list;
	list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
	CHECK_ALLOCATION(list);

	list->head = list->tail = NULL;
	return list;
}

SingleSourceMovesListCell* createSSMListCell(checkersPos* pos, unsigned short capturs, SingleSourceMovesListCell* next) {

	SingleSourceMovesListCell* newCell;
	newCell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
	CHECK_ALLOCATION(newCell);

	newCell->position = pos;
	newCell->captures = capturs;
	newCell->next = next;
	
	return newCell;
}

void insertTreeNodeToStartList(SingleSourceMovesTreeNode* TNode, SingleSourceMovesList* list) {

	SingleSourceMovesListCell* cell = createSSMListCell(TNode->pos, TNode->total_captures_so_far, list->head);
	list->head = cell;

	//if this is the first node
	if (list->tail == NULL)
		list->tail = list->head;

}

void freeList(SingleSourceMovesList* list) {
	SingleSourceMovesListCell* curr = list->head;
	SingleSourceMovesListCell* temp;

	//free the cells in the list
	while (curr != NULL) {
		temp = curr->next;
		free(curr);
		curr = temp;
	}

	//free the list
	free(list);
}