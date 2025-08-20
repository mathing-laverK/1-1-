#include "state.h"
#include <stdio.h>
#include <stdlib.h>

void print_CurrentColor(COLOR* current_color)
{
    if (*current_color == COLOR_WHITE)
        printf("\n--백 자례--\n");
    else if (*current_color == COLOR_BLACK)
        printf("\n--흑 자례--\n");
    else
        printf("\n invalid. current_color undefined\n");

}

void state_init(STATE* state)
{
    printf("=>state_init function/state.c\n");
    state->game_status = IN_PROGRESS;
    state->is_valid = false;
    state->is_castling = false;
    state->is_promotion = false;
    state->is_en_passant = false;
}

GAMESTATUS what_is_state(struct BOARD board, COLOR current_color,  USER user1, USER user2)
{
    printf("=>what_is_state function/state.c\n");
    
    COLOR state_current_color=current_color;
    if (state_current_color == COLOR_WHITE)
        state_current_color = COLOR_BLACK;
    else if (state_current_color == COLOR_BLACK)
        state_current_color = COLOR_WHITE;

    int KING_row, KING_col;
    KING_row = 0;
    KING_col = 0;
    SearchTarget_KING(board, &KING_row, &KING_col, current_color);

    GAMESTATUS timeout_result, mate_result;
    timeout_result = is_timeout(user1, user2, current_color);
    mate_result = is_mate(board, state_current_color, &KING_row, &KING_col);

    if (timeout_result != IN_PROGRESS)
        return timeout_result;
    else
        return mate_result;
}

bool is_valid(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>(%d,%d)->(%d,%d):is_valid function/state.c\n", frow, fcol, trow, tcol);
    bool value_move = false;

    
            /*if (board.squares[frow][fcol]->color == current_color)
        switch (board.squares[frow][fcol]->piece)
        {
            case PAWN:
                value_move = validate_PAWN_move(board, current_color, frow, fcol, trow, tcol);
                break;
            case BISHOP:
                value_move = validate_BISHOP_move(board, current_color, frow, fcol, trow, tcol);
                break;
            case KNIGHT:
                value_move = validate_KNIGHT_move(board, current_color, frow, fcol, trow, tcol);
                break;
            case ROOK:
                value_move = validate_ROOK_move(board, current_color, frow, fcol, trow, tcol);
                break;
            case KING:
                value_move = validate_KING_move(board, current_color, frow, fcol, trow, tcol);
                break;
            case QUEEN:
                value_move = validate_QUEEN_move(board, current_color, frow, fcol, trow, tcol);
                break;
            default:
                value_move = validate_NON_move(board, current_color, frow, fcol, trow, tcol);
                break;
        }
    else
        return false;*/
    if (board.squares[frow][fcol]->color == current_color)
        value_move = (*board.squares[frow][fcol]->rule)(board, current_color, frow, fcol, trow, tcol);

    if (board.squares[frow][fcol]->piece == PAWN)
    {
        if (board.squares[frow][fcol]->color == COLOR_WHITE)
        {
            if (trow == 0)
            {
                return false;
            }

        }
        else if (board.squares[frow][fcol]->color == COLOR_BLACK)
        {
            if (trow == 7)
            {
                return false;
            }
        }
    }


    if (value_move == true)
        printf("true\n");
    else if (value_move == false)
        printf("false\n");

    if (value_move == true)
        return true;
    else
        return false;
}

bool is_check(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{   
    printf("=>is_check function/state.c\n");
    BOARD temp_board;
    for(int i=0; i<8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            temp_board.squares[i][j] = (PIECE*)malloc(sizeof(PIECE));
            if (temp_board.squares[i][j] == NULL)
                free(temp_board.squares[i][j]);
        }
    }
    for(int i=0; i<8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            temp_board.squares[i][j]->color = board.squares[i][j]->color;
            temp_board.squares[i][j]->is_move = board.squares[i][j]->is_move;
            temp_board.squares[i][j]->piece = board.squares[i][j]->piece;
            temp_board.squares[i][j]->rule = board.squares[i][j]->rule;
        }
    }

    if (!(frow == 8 && fcol == 8 && trow == 8 && tcol == 8))
        temp_Board_move(&temp_board, frow, fcol, trow, tcol);

    Board_display(&temp_board);

    int KING_row, KING_col;
    KING_row = 0;
    KING_col = 0;
    SearchTarget_KING(temp_board, &KING_row, &KING_col, current_color);
       
    bool check_state = false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (temp_board.squares[i][j]->color != temp_board.squares[KING_row][KING_col] && temp_board.squares[i][j]-> color != COLOR_NON)
            {
                check_state = is_valid(temp_board, temp_board.squares[i][j]->color, i, j, KING_row, KING_col);
                if (check_state == true)
                    return true;
            }
        }
    }
    return false;

}

GAMESTATUS is_timeout(USER user1, USER user2, COLOR current_color)
{
    printf("=>is_timeout function/state.c\n");
    /*if (user1.color != current_color && user1.time_left == 0)
        return BLACK_WIN;
    else if (user2.color != current_color && user2.time_left == 0)
        return WHITE_WIN;
    else
        return IN_PROGRESS;*/
    return IN_PROGRESS;
}

GAMESTATUS is_mate(struct BOARD board, COLOR current_color,  int* KING_row, int* KING_col)
{
    printf("=>is_mate function/state.c\n");
    // 킹 바로 앞을 막는 경우는 구현. 하지만 멀리 떨어져 있는 곳에서 막는 경우는 구현되지 않았다
    int possible_position[8];
    for (int i = 0; i < 8; i++)
        possible_position[i] = '\0';

    bool state_check = is_check(board, current_color, 8, 8, 8, 8);
    if (state_check == false)
    {
        bool state_draw = is_draw(board,current_color, 8, 8, 8, 8);
        if (state_draw == true)
            return DRAW_STALEMATE;       
        else
            return IN_PROGRESS;
    }  
    else
    {
        int temp_KINGx, temp_KINGy;
        bool temp_ValidEvasion, temp_ValidTakeHide;

        WhereCanGo_KING(board, &KING_row, &KING_col, current_color, possible_position[8]);
        for (int i = 0; i < 8; i++)
        {
            temp_KINGx = possible_position[i] / 10;
            temp_KINGy = possible_position[i] % 10;
            temp_ValidEvasion = validate_KING_move(board, current_color, *KING_row, *KING_col, temp_KINGx, temp_KINGy);
            for (int p = 0; p < 8; p++)
            {
                for (int q = 0; q < 8; q++)
                {
                    if (board.squares[p][q]->color == current_color)
                    {
                        for (int m = 0; m<8 ; m++)
                            for(int n =0; n<8; n++)
                                temp_ValidTakeHide = is_valid(board, current_color, p, q, m, n);
                    }
                }
            }

            if (temp_ValidEvasion || temp_ValidTakeHide)
            {
                return IN_PROGRESS;
            }
            else
            {
                if (current_color == COLOR_BLACK)
                    return WHITE_WIN;
                else if (current_color == COLOR_WHITE)
                    return BLACK_WIN;
            }
        }
    }
}

bool is_castling(struct BOARD* board, int frow, int fcol, int trow, int tcol)
{
    return false;
}

GAMESTATUS is_draw(struct BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    return false;
}
