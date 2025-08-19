#ifndef PIECE_H
#define PIECE_H

#include "color.h"
#include <stdbool.h>
struct BOARD;


typedef enum
{
    PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING, PIECE_NON
}CHESS_PIECE;

typedef bool (*Rule_Func)(struct BOARD, COLOR, int, int, int, int);

typedef struct 
{
    CHESS_PIECE piece;
    COLOR color;
    int is_move;
    Rule_Func rule;
}PIECE;

#endif 