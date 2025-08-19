#ifndef RULE_H
#define RULE_H

#include <stdbool.h>
#include "color.h"
#include "board.h"

bool validate_NON_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_PAWN_move( BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_BISHOP_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_KNIGHT_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_ROOK_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_KING_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_QUEEN_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_PROMOTION_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool validate_CASTLING_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool is_forward(BOARD baord, int frow, int fcol, int trow, int tcol);
bool is_PathClear(BOARD board, int frow, int fcol, int trow, int tcol, int temp_gapROW, int temp_gapCOL);

int gap(int a, int b);
 
#endif