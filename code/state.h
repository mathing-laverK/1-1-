#ifndef STATE_H
#define STATE_H

#include "rule.h"
#include "color.h"
#include "user.h"
#include "board.h"

typedef enum GAMESTATUS{
    IN_PROGRESS,
    WHITE_WIN,
    BLACK_WIN,
    DRAW_STALEMATE,
    DRAW_3FOLD,
    DRAW_AGREEMENT,
    DRAW_50MOVE
}GAMESTATUS;


typedef struct STATE {
    bool is_valid;
    GAMESTATUS game_status;
    bool is_castling;
    bool is_promotion;
    bool is_en_passant;
}STATE;

void state_init(STATE* state);
GAMESTATUS is_draw(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
GAMESTATUS is_mate(struct BOARD board, COLOR current_color, int* KING_row, int* KING_col);
GAMESTATUS is_timeout(USER user1, USER user2, COLOR current_color);

GAMESTATUS what_is_state(struct BOARD board, COLOR current_color, USER user1, USER user2);

bool is_valid(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool is_check(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol);
bool is_castling(struct BOARD* board, int frow, int fcol, int trow, int tcol);

void print_CurrentColor(COLOR* current_color);

#endif