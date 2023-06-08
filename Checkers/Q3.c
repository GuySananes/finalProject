#include "checkers.h"

//Q3
/************************************************************************************************/

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

bool isTreeEmptyOrOneNode(SingleSourceMovesTree* Tree) {
	return (Tree == NULL || (Tree->source->nextMoves[0] == NULL && Tree->source->nextMoves[1] == NULL));
}


multipleSourceMovesList* makeEmptyMSMList() {
	multipleSourceMovesList* multplmoveslst;

	multplmoveslst = (multipleSourceMovesList*)malloc(sizeof(multipleSourceMovesList));
	CHECK_ALLOCATION(multplmoveslst);

	multplmoveslst->head = NULL;
	multplmoveslst->tail = NULL;

	return multplmoveslst;

}

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






