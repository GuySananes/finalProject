#ifndef  __CHECKERS_H
#define __CHECKERS_H

//include
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//defines
#define _CRT_SECURE_NO_WARNINGS
#define BOARD_SIZE 8
#define WHITE_SQUARE 'X'
#define EMPTY_SQUARE 'E'
#define PLAYER_1 'T'
#define PLAYER_2 'B'
#define LEFT 0
#define RIGHT 1
#define OPPOSITE_DIRECTION -1
#define STEP 1
#define CAPTURE 2
#define NO_MOVES 0
#define NO_CAPTURES 0

//emun
enum ROWS_LETTER
{
	A, B, C, D,	E, F, G, H
};

//macros
#define IS_GRAY_SQUARE(row, col)   (((row + col)%2 != 0) ? 1 : 0)
#define WHICH_PLAYER(player) ((player == PLAYER_1) ? 1 : -1)
#define SET_DIR(d) ((d == RIGHT) ? -1 : 1)

//typdefs
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef unsigned short int USint;

//structs
typedef struct _checkersPos {
	char row;
	char col;
}checkersPos;

typedef struct _SingleSourceMovesTreeNode {
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far;
	struct _SingleSourceMovesTreeNode* nextMoves[2];
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree {
	SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;

typedef struct _SingleSourceMovesListCell {
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList {
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell {
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;
}multipleSourceMovesListCell;

typedef struct _multipleSourceMovesList {
	multipleSourceMovesListCell* head;
	multipleSourceMovesListCell* tail;
}multipleSourceMovesList;


//functions

//general game functions

void initGame(Board board);
void printBoard(Board board);

//Q1
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
void FindSingleSourceMovesHelper(Board board, SingleSourceMovesTreeNode* src, USint player);
void buildssmSubTree(Board board, SingleSourceMovesTreeNode* src, USint nextMove, USint dir);
USint findMoveType(Board board, checkersPos* pos, USint dir);

//Q2


//Q3


//Q4


//Q5


//Trees function
SingleSourceMovesTree* makeEmptyTree();
SingleSourceMovesTreeNode* createSSMTreeNode(Board board, checkersPos* pos, unsigned short totalCaptures, SingleSourceMovesTreeNode* LeftnextMove, SingleSourceMovesTreeNode* RightnextMove);

//etc

void checkAllocaiton(void* p);
void copyBoard(Board dest, Board source);


#endif // ! __CHECKERS_H

