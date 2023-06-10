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
#define WHITE_SQUARE ' '
#define EMPTY_SQUARE ' '
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
enum ROWS_LETTER{ A, B, C, D, E, F, G, H };

//macros
#define IS_GRAY_SQUARE(row, col)   (((row + col)%2 != 0) ? 1 : 0)
#define WHICH_PLAYER(player) ((player == PLAYER_1) ? 1 : -1)
#define SET_DIR(d) ((d == RIGHT) ? -1 : 1)
#define PLAYER_TO_CHAR(P) ((P == 1) ? PLAYER_1 : PLAYER_2)
#define CHECK_ALLOCATION(p) if(p == NULL) {printf("Memorey allocation failed!\n"); exit(1);}
#define SWITCH_PLAYERS(player) ((player == PLAYER_1) ? PLAYER_2 : PLAYER_1)
#define GET_AVG_POS(a,b) ((a + b) / 2)
#define PRINT_LINE puts("+-+-+-+-+-+-+-+-+-+")
#define PRINT_NUMBERS puts("+ |1|2|3|4|5|6|7|8|")

//typdefs
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];
typedef unsigned char Player;
typedef short int Sint;

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
void initGameHelper(int start, int end, char tool, Board board);
void printBoard(Board board);

//Q1
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);
void FindSingleSourceMovesHelper(Board board, SingleSourceMovesTreeNode* src, Sint player);
void buildssmSubTree(Board board, SingleSourceMovesTreeNode* src, Sint nextMoveType, Sint dir);
Sint findMoveType(Board board, checkersPos* pos, Sint dir);
void addNextCaptureNode(Board board, SingleSourceMovesTreeNode* src, Sint player, Sint captures, Sint dir);

//Q2
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
SingleSourceMovesList* FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* src);

//Q3
multipleSourceMovesList* FindAllPossibleMoves(Board board, Player player);
bool isTreeEmptyOrOneNode(SingleSourceMovesTree* Tree);
void FindAllPossibleMovesHelper(int row, int col, Board board, multipleSourceMovesList* multplmoveslst);
multipleSourceMovesList* makeEmptyMSMList();
void insertDataToEndMSMList(SingleSourceMovesList* curList, multipleSourceMovesList* multplmoveslst);
multipleSourceMovesListCell* createMSMListCell(SingleSourceMovesList* curList, multipleSourceMovesListCell* next);
void insertCellToEndMSMList(multipleSourceMovesListCell* NewCell, multipleSourceMovesList* multplmoveslst);

//Q4
void Turn(Board board, Player player);
SingleSourceMovesList* getOptimalMove(Board board, Player player, multipleSourceMovesList* multipleMovesLst);
void updateBoard(Board board, Player player, SingleSourceMovesList* moves_list);  


//Q5
void PlayGame(Board board, Player starting_player);
void gamePlayLoop(Board board, Player player);
bool isGameOver(Board board, Player player);

//Trees function
SingleSourceMovesTree* makeEmptyTree();
SingleSourceMovesTreeNode* createSSMTreeNode(Board board, checkersPos* pos, unsigned short int totalCaptures, SingleSourceMovesTreeNode* LeftnextMove, SingleSourceMovesTreeNode* RightnextMove);
void freeSSMTree(SingleSourceMovesTree* tree);
void freeSSMTreeHelper(SingleSourceMovesTreeNode* src);

//SingleSourceMoves list fucntions
SingleSourceMovesList* makeEmptySSMList();
SingleSourceMovesListCell* createSSMListCell(checkersPos* pos, unsigned short capturs, SingleSourceMovesListCell* next);
void insertTreeNodeToStartList(SingleSourceMovesTreeNode* TNode, SingleSourceMovesList* list);
void freeList(SingleSourceMovesList* list);

//general functions
void copyBoard(Board dest, Board source);


#endif // ! __CHECKERS_H

