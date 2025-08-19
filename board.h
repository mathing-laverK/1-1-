#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "movelog.h"

typedef struct BOARD
{
    MoveLog* MoveLog_history;
    PIECE* squares[8][8];
}BOARD;

void Board_init(BOARD* board);

void Board_move(BOARD* board, int frow, int fcol, int trow, int tcol);
void temp_Board_move(BOARD* board, int frow, int fcol, int trow, int tcol);

void Board_MakeMoveLog(BOARD* board, int frow, int fcol, int trow, int tcol, int state);
void Board_display(BOARD* board);

void Board_CastlingMove(BOARD* board, int forx, int fory, int tox, int toy);

void SearchTarget_KING(BOARD board, int* KING_row, int* KING_col, COLOR current_color);
void WhereCanGo_KING(BOARD board, int* KING_row, int* KING_col, COLOR current_color, int possible_position[8]);

#endif