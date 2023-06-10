#include "checkers.h"

//Q3
/************************************************************************************************/


/************************
* Input: board and player
* Output: multiple source moves list
* Function operation: goes through each position on the board and checks
* if it is the current players pos. sends the position of all player's spots to the helper,
************************/
multipleSourceMovesList* FindAllPossibleMoves(Board board, Player player) {

	multipleSourceMovesList* multplmoveslst = makeEmptyMSMList();
	int i = 0, j = 0;	
	
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			if (board[i][j] == player)
				FindAllPossibleMovesHelper(i, j, board, multplmoveslst);
		}
	}

	return multplmoveslst;
}

/************************
* Input: row and col of a spot that contains the current player
* Output: void
* Function operation: if the current player can move from this spot, it adds the path to the list.
* the path is the single source moves list. which is becoming (sort of) a node in the multiple moves list.
************************/
void FindAllPossibleMovesHelper(int row, int col, Board board, multipleSourceMovesList* multplmoveslst) {

	checkersPos* curPos;
	SingleSourceMovesTree* curTree;
	SingleSourceMovesList* curList;

	curPos = (checkersPos*)malloc(sizeof(checkersPos));
	CHECK_ALLOCATION(curPos);

	curPos->row = row;
	curPos->col = col;
	curTree = FindSingleSourceMoves(board, curPos);

	if (!isTreeEmptyOrOneNode(curTree))
	{
		curList = FindSingleSourceOptimalMove(curTree);
		insertDataToEndMSMList(curList, multplmoveslst);
	}

}
//checks if the tree is empty or only has one node,
//if it is empty or one node only,there are no moves from this position.
bool isTreeEmptyOrOneNode(SingleSourceMovesTree* Tree) {
	return (Tree == NULL || (Tree->source->nextMoves[0] == NULL && Tree->source->nextMoves[1] == NULL));
}

//lists functions to insert new cells to the multiple source moves list...
multipleSourceMovesList* makeEmptyMSMList() {
	multipleSourceMovesList* multplmoveslst;

	multplmoveslst = (multipleSourceMovesList*)malloc(sizeof(multipleSourceMovesList));
	CHECK_ALLOCATION(multplmoveslst);

	multplmoveslst->head = NULL;
	multplmoveslst->tail = NULL;

	return multplmoveslst;

}


//MSM = multiple source moves list
void insertDataToEndMSMList(SingleSourceMovesList* curList, multipleSourceMovesList* multplmoveslst) {

	multipleSourceMovesListCell* NewCell;

	NewCell = createMSMListCell(curList, NULL);
	insertCellToEndMSMList(NewCell, multplmoveslst);
	
}

multipleSourceMovesListCell* createMSMListCell(SingleSourceMovesList* curList, multipleSourceMovesListCell* next) {

	multipleSourceMovesListCell* NewCell;

	NewCell = (multipleSourceMovesListCell*)malloc(sizeof(multipleSourceMovesListCell));
	CHECK_ALLOCATION(NewCell);

	NewCell->single_source_moves_list = curList;
	NewCell->next = next;

	return NewCell;
}

void insertCellToEndMSMList(multipleSourceMovesListCell* NewCell, multipleSourceMovesList* multplmoveslst) {

	if (multplmoveslst->tail == NULL)
		multplmoveslst->head = multplmoveslst->tail = NewCell;
	else
	{
		multplmoveslst->tail->next = NewCell;
		multplmoveslst->tail = NewCell;
	}
}






