#ifndef CHESS_H
#define CHESS_H

#include "board.h"
#include "input.h"
#include "user.h"
#include "state.h"
#include "color.h"

typedef struct {
    USER user1;
    USER user2;
    BOARD board;
    INPUT input;
    STATE state;
    COLOR current_color;
    int move_count;
}CHESS;

void chess_init(CHESS* game);
void chess_run(CHESS* game);

#endif 
