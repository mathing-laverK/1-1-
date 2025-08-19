#include "rule.h"
#include <stdio.h>
#include <string.h>

bool validate_NON_move(BOARD board, COLOR current_color, int frow, int fcol, int trwo, int tcol)
{
    return false;
}

int gap(int a, int b)
{
    printf("=>gap function/rule.c\n");
    if (a >= b)
        return a - b;
    else if (a < b)
        return b - a;
}

bool is_forward(BOARD board, int frow, int fcol, int trow, int tcol)
{
    printf("=>is_forward function/rule.c\n");
    if (board.squares[frow][fcol]->color == COLOR_WHITE)
    {
        if (frow > trow)
            return true;
        else
            return false;
    }
    else if (board.squares[frow][fcol]->color == COLOR_BLACK)
    {
        if (frow < trow)
            return true;
        else
            return false;
    }    
}

bool is_PathClear(BOARD board, int frow, int fcol, int trow, int tcol, int temp_gapROW, int temp_gapCOL)
{
    printf("=>is_PathClear function/rule.c\n");
    if ((temp_gapROW == 0) ^ (temp_gapCOL == 0))
    {
        if (temp_gapROW == 0)
        {
            if (fcol < tcol)
            {
                for (int i = fcol + 1; i <= tcol - 1; i++)
                    if (board.squares[frow][i]->piece != PIECE_NON)
                    {
                        return false;
                    }

                return true;
            }
            if (fcol > tcol)
            {
                for (int i = tcol + 1; i <= fcol - 1; i++)
                    if (board.squares[frow][i]->piece!= PIECE_NON)
                    {
                        return false;
                    }

                return true;
            }
        }
        else if (temp_gapCOL == 0)
        {
            if (frow < trow)
            {
                for (int i = frow + 1; i <= trow - 1; i++)
                    if (board.squares[i][fcol]->piece != PIECE_NON)
                    {
                        return false;
                    }

                return true;
            }
            if (frow > trow)
            {
                for (int i = trow + 1; i <= frow - 1; i++)
                    if (board.squares[i][fcol]->piece!= PIECE_NON)
                    {
                        return false;
                    }

                return true;
            }
        }
    }
    else if ((frow-trow) / (fcol-tcol) < 0)
    {
        if (frow < trow)
        {
            int i, j;
            for (i= frow+1, j= fcol-1; (i<=trow-1) && (j>=tcol+1); i++, j--)
                if (board.squares[i][j]->piece != PIECE_NON)
                {   
                    return false;
                }

            return true;
        }
        else if (frow > trow)
        {
            int i, j;
            for (i = frow-1, j = fcol+1; (i >= trow+1) && (j <= tcol-1); i--, j++)
                if (board.squares[i][j]->piece != PIECE_NON)
                {
                    return false;
                }

            return true;
        }

    }
    else if ((frow - trow) / (fcol - tcol) > 0)
    {
        if (frow < trow)
        {
            int i, j;
            for (i = frow+1, j = fcol+1; (i <= trow-1) && (j <= tcol-1); i++, j++)
                if (board.squares[i][j]->piece != PIECE_NON)
                {
                    return false;
                }

            return true;
        }
        else if (frow > trow)
        {
            int i, j;
            for (i = frow-1, j = fcol-1; (i >= trow+1) && (j >= tcol+1); i--, j--)
                if (board.squares[i][j]->piece != PIECE_NON)
                {
                    return false;
                }

            return true;
        }
    }
    else
    {
        return false;
    }
}

bool validate_PAWN_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_PAWN_move function/rule.c\n");
    int temp_gapROW, temp_gapCOL;
    temp_gapROW = gap(frow, trow);
    temp_gapCOL = gap(fcol, tcol);

    if (temp_gapROW == 1 && temp_gapCOL == 0 && is_forward(board,frow, fcol, trow, tcol))
    {
        if (board.squares[trow][tcol]->piece == PIECE_NON)
            return true;
        else
            return false;
    }
    else if (temp_gapROW == 2 && temp_gapCOL == 0 && board.squares[trow][tcol]->piece == PIECE_NON && is_forward(board, frow, fcol, trow, tcol))
    {
        if (board.squares[frow][fcol]->is_move == 0)
        {
            if (board.squares[frow][fcol]->color == COLOR_WHITE && board.squares[frow - 1][fcol]->piece == PIECE_NON)
                return true;
            else if (board.squares[frow][fcol]->color == COLOR_BLACK && board.squares[frow + 1][fcol]->piece == PIECE_NON)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    else if (temp_gapROW == 1 && temp_gapCOL == 1 && is_forward)
    {
        if (board.squares[trow][tcol]->color != current_color && board.squares[trow][tcol]->color != COLOR_NON)
            return true;
        else if(board.squares[frow][fcol-1]->piece != PIECE_NON || board.squares[frow][fcol+1]->piece != PIECE_NON)
        {
            if (board.squares[frow][fcol - 1]->piece != PIECE_NON && board.squares[trow][tcol]->color != current_color)
            {
                if (board.squares[frow][fcol - 1]->is_move != 1)
                    return true;
                else
                    return false;
            }
            else if (board.squares[frow][fcol + 1]->piece != PIECE_NON && board.squares[trow][tcol]->color != current_color)
            {
                if (board.squares[frow][fcol + 1]->is_move != 1)
                    return true;
                else
                    return false;
            }
        }
        else
            return false;
    }
    else
        return false;
}

bool validate_BISHOP_move(BOARD board, COLOR current_color,int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_BISHOP_move function/rule.c\n");
    int temp_gapROW, temp_gapCOL;
    temp_gapROW = gap(frow, trow);
    temp_gapCOL = gap(fcol, tcol);
    
    if (board.squares[trow][tcol]->color != current_color)
    {
        if (temp_gapROW == temp_gapCOL && temp_gapROW != 0)
        {
            bool valid = is_PathClear(board, frow, fcol, trow, tcol, temp_gapROW, temp_gapCOL);
            return valid;
        }
        else
            return false;
    }
    else
        return false;

}

bool validate_KNIGHT_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_KNIGHT_move function/rule.c\n");
    int temp_gapROW, temp_gapCOL;
    temp_gapROW = gap(frow, trow);
    temp_gapCOL = gap(fcol, tcol);


    if (temp_gapCOL != 0)
    {
        float temp_inclination = (float) temp_gapROW / temp_gapCOL;

        if (board.squares[trow][tcol]->color != current_color || board.squares[trow][tcol]->piece == PIECE_NON)
        {
            if(temp_gapROW<=2 || temp_gapCOL<=2)
            {
                if (temp_inclination == 2 || temp_inclination == 0.5)
                {
                    return true;
                }
                else
                    return false;
            }
        }
    }
    else
        return false;
}

bool validate_ROOK_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_ROOK_move function/rule.c\n");
    int temp_gapROW, temp_gapCOL;
    temp_gapROW = gap(frow, trow);
    temp_gapCOL = gap(fcol, tcol);


    if (board.squares[trow][tcol]->color != current_color || board.squares[trow][tcol]->piece == PIECE_NON)
    {
        if (temp_gapROW == 0 || temp_gapCOL == 0)
        {
            bool valid = is_PathClear(board, frow, fcol, trow, tcol, temp_gapROW, temp_gapCOL);
            return valid;
        }
        else
            return false;
    }
    else
        return false;
}

bool validate_KING_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_KING_move function/rule.c\n");
    int temp_gapROW, temp_gapCOL;
    temp_gapROW = gap(frow, trow);
    temp_gapCOL = gap(fcol, tcol);

    if (board.squares[trow][tcol]->color != current_color || board.squares[trow][tcol]->piece == PIECE_NON)
    {
        if (temp_gapROW == 1 || temp_gapCOL == 1)
        {
            bool KINGmove = validate_QUEEN_move(board, current_color, frow, fcol, trow, tcol);
            return KINGmove;
        }
        else
            return false;
    }
    else
        return false;
}

bool validate_QUEEN_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    printf("=>validate_QUEEN_move function/rule.c\n");
    int temp_gapX, temp_gapY;
    temp_gapX = gap(frow, trow);
    temp_gapY = gap(fcol, tcol);

    if (temp_gapX == temp_gapY && temp_gapX != 0 && temp_gapY != 0)
    {
        bool QUEEN_BISHOPmove = validate_BISHOP_move(board, current_color, frow, fcol, trow, tcol);
        return QUEEN_BISHOPmove;
    }
    else if (temp_gapX == 0 && temp_gapY != 0 || temp_gapX != 0 && temp_gapY == 0)
    {
        bool QUEEN_ROOKmove = validate_ROOK_move(board, current_color, frow, fcol, trow, tcol);
        return QUEEN_ROOKmove;
    }
    else
        return false;
}

bool validate_PROMOTION_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    return false;
}

bool validate_CASTLING_move(BOARD board, COLOR current_color, int frow, int fcol, int trow, int tcol)
{
    return false;
}
