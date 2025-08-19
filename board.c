#include "board.h"
#include "rule.h"
#include "piece.h"
#include <stdio.h>
#include <stdlib.h>

void Board_init(BOARD* board) 
{
    printf("=> Board_init function/board.c\n");
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            board->squares[i][j] = (PIECE*)malloc(sizeof(PIECE));
            if (board->squares[i][j] == NULL)
                free(board->squares[i][j]);

            board->squares[i][j]->is_move = 0;//이거 왜 이렇게 선언해야하는지 이해해야할 필요가 있음
        }

    board->squares[0][0]->piece = board->squares[0][7]->piece = board->squares[7][0]->piece = board->squares[7][7]->piece = ROOK;
    board->squares[0][1]->piece = board->squares[0][6]->piece = board->squares[7][1]->piece = board->squares[7][6]->piece = KNIGHT;
    board->squares[0][2]->piece = board->squares[0][5]->piece = board->squares[7][2]->piece = board->squares[7][5]->piece = BISHOP;
    board->squares[0][3]->piece = board->squares[7][3]->piece = QUEEN;
    board->squares[0][4]->piece = board->squares[7][4]->piece = KING;
    for (int i = 0; i < 8; i++)
    {
        board->squares[1][i]->piece = board->squares[6][i]->piece = PAWN;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 8; j++)
            board->squares[i][j]->color = COLOR_BLACK;
    }
    for (int i = 7; i > 5; i--)
    {
        for (int j = 0; j < 8; j++)
            board->squares[i][j]->color = COLOR_WHITE;
    }
    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board->squares[i][j]->color = COLOR_NON;
            board->squares[i][j]->piece = PIECE_NON;
            board->squares[i][j]->is_move = -1;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (board->squares[i][j]->piece)
            {
            case PAWN:
                board->squares[i][j]->rule = &validate_PAWN_move;
                break;
            case ROOK:
                board->squares[i][j]->rule = &validate_ROOK_move;
                break;
            case KNIGHT:
                board->squares[i][j]->rule = &validate_KNIGHT_move;
                break;
            case BISHOP:
                board->squares[i][j]->rule = &validate_BISHOP_move;
                break;
            case QUEEN:
                board->squares[i][j]->rule = &validate_QUEEN_move;
                break;
            case KING:
                board->squares[i][j]->rule = &validate_KING_move;
                break;
            default:
                board->squares[i][j]->rule = &validate_NON_move;
                break;

            }
        }
    }
}

void Board_display(BOARD* board)
{
    printf("=> Board_display function/board.c\n");
    printf("\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board->squares[i][j]->color == COLOR_WHITE)
            {
                if (board->squares[i][j]->piece == PAWN)
                    printf("P ");
                else if (board->squares[i][j]->piece == ROOK)
                    printf("R ");
                else if (board->squares[i][j]->piece == KNIGHT)
                    printf("N ");
                else if (board->squares[i][j]->piece == BISHOP)
                    printf("B ");
                else if (board->squares[i][j]->piece == QUEEN)
                    printf("Q ");
                else if (board->squares[i][j]->piece == KING)
                    printf("K ");
            }
            else if (board->squares[i][j]->color == COLOR_BLACK)
            {
                if (board->squares[i][j]->piece == PAWN)
                    printf("p ");
                else if (board->squares[i][j]->piece == ROOK)
                    printf("r ");
                else if (board->squares[i][j]->piece == KNIGHT)
                    printf("n ");
                else if (board->squares[i][j]->piece == BISHOP)
                    printf("b ");
                else if (board->squares[i][j]->piece == QUEEN)
                    printf("q ");
                else if (board->squares[i][j]->piece == KING)
                    printf("k ");
            }
            else
                printf("# ");

            if (j == 7)
                printf("\n");

        }
    }
    printf("\n");
}

void Board_move(BOARD* board, int frow, int fcol, int trow, int tcol)
{
    printf("=> Board_move function/board.c\n");
    board->squares[trow][tcol]->color = board->squares[frow][fcol]->color;
    board->squares[trow][tcol]->is_move = board->squares[frow][fcol]->is_move;
    board->squares[trow][tcol]->piece = board->squares[frow][fcol]->piece;
    board->squares[trow][tcol]->rule = board->squares[frow][fcol]->rule;

    free(board->squares[frow][fcol]);
    board->squares[frow][fcol] = malloc(sizeof(PIECE));
    if(board->squares[frow][fcol]==NULL)
        free(board->squares[frow][fcol]);
    else
    {
        board->squares[frow][fcol]->color = COLOR_NON;
        board->squares[frow][fcol]->is_move = 0;
        board->squares[frow][fcol]->piece = PIECE_NON;
        board->squares[frow][fcol]->rule = &validate_NON_move;
    }

}

void temp_Board_move(BOARD* board, int frow, int fcol, int trow, int tcol)
{
    printf("=> temp_Board_move function/board.c\n");
    board->squares[trow][tcol]->color = board->squares[frow][fcol]->color;
    board->squares[trow][tcol]->is_move = board->squares[frow][fcol]->is_move;
    board->squares[trow][tcol]->piece = board->squares[frow][fcol]->piece;
    board->squares[trow][tcol]->rule = board->squares[frow][fcol]->rule;

    //기존의 메모리를 free 하지 않고 다시 malloc으로 선언해서 써도 되나?
    free(board->squares[frow][fcol]);
    board->squares[frow][fcol] = malloc(sizeof(PIECE));
    if (board->squares[frow][fcol] == NULL)
        free(board->squares[frow][fcol]);
    else
    {
        board->squares[frow][fcol]->color = COLOR_NON;
        board->squares[frow][fcol]->is_move = 0;
        board->squares[frow][fcol]->piece = PIECE_NON;
        board->squares[frow][fcol]->rule = &validate_NON_move;
    }
}

void Board_MakeMoveLog(BOARD* board, int forx, int fory, int tox, int toy, int state)
{

}

void Board_CastlingMove(BOARD* board, int forx, int fory, int tox, int toy)
{
   
}

void Board_MakeMoveLogCastling(BOARD* board, int forx, int fory, int tox, int toy)
{

}

void SearchTarget_KING(BOARD board, int* KING_row, int* KING_col, COLOR current_color)
{
    printf("=> SearchTarget_KING function/board.c\n");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board.squares[i][j]->piece == KING && board.squares[i][j]->color == current_color )
            {
                *KING_row = i;
                *KING_col = j;
            }  
        }
    }
}

void WhereCanGo_KING(BOARD board, int* KING_x, int* KING_y, COLOR current_color, int possible_position[8])
{
    printf("=> WhereCanGo_KING function/board.c\n");
    
    int count = 0;
    for (int i = *KING_x - 1; i < *KING_x + 1; i++)
    {
        for (int j = *KING_y - 1; j < *KING_y + 1; j++)
        {
            if (i >= 0 && i < 8 && j >= 0 && j < 8)
            {
                *(possible_position + count) = 10 * i + j;
                count++;
            }
        }
    }
}
