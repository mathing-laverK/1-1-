#include "chess.h"
#include <stdio.h>
#include <string.h>

void chess_init(CHESS* game)
{
    printf("=>chess_init function/chess.c\n");
    game->current_color = COLOR_WHITE;
    game->move_count = 0;

    state_init(&game->state);//���� ���� �ʱ�ȭ

    input_init(&game->input);

    user1_init(&game->user1);//user1 ���� �ʱ�ȭ
    user2_init(&game->user2);//user2 ���� �ʱ�ȭ

    Board_init(&game->board);//���� �ʱ�ȭ+�⹰ �ʱ�ȭ(�⹰ ��ġ �ʱ�ȭ+�⹰ ������ ���� �Լ� ������ ����)+�⹰ ���
}

void chess_run(CHESS* game)//�ٸ� ��ü���� ��ȯ�� ���� ���� ������ ��� �������� �����ϴ� ��ü��
{
    printf("=>chess_run function/chess.c\n");
    while (game->state.game_status == IN_PROGRESS)
    {
        int ItIsDraw_agree=0;//���� ���º��� ��� �ٸ� ���� ���� ������ ������ ����Ǿ���ϹǷ� ���� while�� Ż���ϱ� ���� ���� while���� �������� ���� ���º� ���ο� ���� ��ȭ�ϸ� �ܺ� while������ Ż���� �����ϵ��� ��
        while(1)
        {
            if (game->current_color == COLOR_WHITE)
                printf("\n--turn: COLOR_WHITE--\n");
            else if (game->current_color == COLOR_BLACK)
                printf("\n--turn: COLOR_BLACK--\n");

            Board_display(&game->board);          

            //�Ϲ����� �Է°� �����ӿ� ���� Ÿ�缺 �κ�: (1)�Է°��� ��ȿ�� (2)������ Ÿ�缺 ��
            // �Է°����� input.c���� ����ϴ°� ����->�Űܾ���
            while (1)
            {
                printf("Select the square containing the piece you want to move: \n");
                scanf("%s", game->input.For_user_input);
                INPUT valid_ConvertForInput = convert_for_input(&game->input);
                bool is_castling = is_special(&game->input);
                bool input_IsDraw = is_DrawAgree(&game->input.For_user_input);
                if (is_castling == true)
                    goto castling_move;

                if (input_IsDraw == true)
                {
                    char temp[20];
                    temp[0] = '\0';
                    
                    printf("YES or N0: \n");
                    scanf("%s", temp);
                    if (strcmp(temp, "YES") == 0)
                    {   
                        ItIsDraw_agree = 1;
                        game->state.game_status = DRAW_AGREEMENT;
                        break;
                    }
                    else if (strcmp(temp, "NO") == 0)
                    {
                        continue;
                    }
                }

                if (valid_ConvertForInput.is_valid == false)
                {
                    printf("INVALID INPUT! TRY AGAIN\n");
                    continue;
                }
                else
                    break;
            }// for A to B: A�� �ش��ϴ� ���� ������ �Ǵ� + Ư�� ��Ģ �������� ���� �Է����� �Ǵ� + ���� ���ºθ� ���� �Է����� �Ǵ�

            if (ItIsDraw_agree == 1)
                break;

            // �Է°����� input.c���� ����ϴ°� ����->�Űܾ���
            while(1)           
            {
                printf("Select which square you want to move the piece to: \n");
                scanf("%s", game->input.To_user_input);
                INPUT to_input = convert_to_input(&game->input);
                if (to_input.is_valid == false)
                {
                    printf("INVALID INPUT! TRY AGAIN\n");
                    continue;
                }
                else
                    break;
            }

            //--����ڷκ��� �Է°��� �ް�(���ڿ��� ������ �� �ִ��� �˻�) �Է°��� ��ǥ�� ��ȯ(ü�� �����ǿ��� ����� �� �ִ� ��ǥ���� �˻�)--
            
            CHESS move_IsValid;
            move_IsValid.state.is_valid = false;

            bool value_move = is_valid(game->board, game->current_color, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col);
            bool value_check = is_check(game->board, game->current_color, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col);


            if(value_move == true)
            {
                if (value_check == false)
                    move_IsValid.state.is_valid = true;
                else
                {
                    printf("value_check:TRUE...ILLEGAL MOVE! TRY AGAIN\n");
                    move_IsValid.state.is_valid = false;
                }
            }
            else
            {
                printf("value_move:FALSE...ILLEGAL MOVE! TRY AGAIN\n");
                continue;
            }

            CHESS moveCastling_IsValid;
        castling_move:
            moveCastling_IsValid.state.is_valid = false;
            moveCastling_IsValid.state.is_valid = is_castling(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col);
            if (value_move == true && value_check == false)
                move_IsValid.state.is_valid = true;
            
            if (move_IsValid.state.is_valid == true)
            {   
                game->board.squares[game->input.For_row][game->input.For_col]->is_move++;
                Board_move(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col);
                input_init(&game->input);
            }
            else if (moveCastling_IsValid.state.is_valid == true)
            {
                game->board.squares[game->input.For_row][game->input.For_col]->is_move++;
                //Board_CastlingMove(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col); ���� �������� ����                
                input_init(&game->input);
            }
            else
            {
                printf("ILLEGAL MOVE! TRY AGAIN\n");
                continue;
            }

            game->state.game_status = what_is_state(game->board, game->current_color, game->user1, game->user2);
            //if (what_is_state == IN_PROGRESS)
                

                //Board_MakeMoveLog(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col, 1);
                //Board_MakeMoveLog(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col, 2);
            if (game->state.game_status != IN_PROGRESS)
                break;
            else
            {
                if (game->current_color == COLOR_WHITE)
                    game->current_color = COLOR_BLACK;
                else if (game->current_color == COLOR_BLACK)
                    game->current_color = COLOR_WHITE;

                game->move_count++;
                continue;
            }
            /*if (game->current_color == COLOR_WHITE)
                game->current_color = COLOR_BLACK;
            else if (game->current_color == COLOR_BLACK)
                game->current_color = COLOR_WHITE;*/
        }
        if (ItIsDraw_agree == 1)
            break;
    }

    switch (game->state.game_status) 
    {   
        case DRAW_STALEMATE:
            printf("\n--DRAW_STALEMATE--\n");
            break;
        case DRAW_3FOLD:
            printf("\n--DRAW_3FOLD--\n");
            break;
        case DRAW_AGREEMENT:
            printf("\n--DRAW_AGREEMENT--\n");
            break;
        case DRAW_50MOVE:
            printf("\n--DRAW_50MOVE--\n");
            break;
        case WHITE_WIN:
            printf("\n--WHITE_WIN--\n");
            break;
        case BLACK_WIN:
            printf("\n--BLACK_WIN--\n");
            break;
    }
}