#include "chess.h"
#include <stdio.h>
#include <string.h>

void chess_init(CHESS* game)
{
    printf("=>chess_init function/chess.c\n");
    game->current_color = COLOR_WHITE;
    game->move_count = 0;

    state_init(&game->state);//게임 상태 초기화

    input_init(&game->input);

    user1_init(&game->user1);//user1 정보 초기화
    user2_init(&game->user2);//user2 정보 초기화

    Board_init(&game->board);//보드 초기화+기물 초기화(기물 위치 초기화+기물 종류에 따라 함수 포인터 연결)+기물 출력
}

void chess_run(CHESS* game)//다른 객체들이 반환한 값에 따라 게임을 어떻게 진행할지 결정하는 객체임
{
    printf("=>chess_run function/chess.c\n");
    while (game->state.game_status == IN_PROGRESS)
    {
        int ItIsDraw_agree=0;//합의 무승부인 경우 다른 조건 없이 무조건 게임이 종료되어야하므로 이중 while을 탈출하기 위해 내부 while에서 변수값이 합의 무승부 여부에 따라 변화하면 외부 while에서도 탈출이 가능하도록 함
        while(1)
        {
            if (game->current_color == COLOR_WHITE)
                printf("\n--turn: COLOR_WHITE--\n");
            else if (game->current_color == COLOR_BLACK)
                printf("\n--turn: COLOR_BLACK--\n");

            Board_display(&game->board);          

            //일반적인 입력과 움직임에 대한 타당성 부분: (1)입력값의 유효성 (2)움직임 타당성 평가
            // 입력관련은 input.c에서 담당하는게 옳음->옮겨야함
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
            }// for A to B: A에 해당하는 값의 적절성 판단 + 특수 규칙 움직임을 위한 입력인지 판단 + 합의 무승부를 위한 입력인지 판단

            if (ItIsDraw_agree == 1)
                break;

            // 입력관련은 input.c에서 담당하는게 옳음->옮겨야함
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

            //--사용자로부터 입력값을 받고(문자열로 저장할 수 있는지 검사) 입력값을 좌표로 변환(체스 보드판에서 사용할 수 있는 좌표인지 검사)--
            
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
                //Board_CastlingMove(&game->board, game->input.For_row, game->input.For_col, game->input.To_row, game->input.To_col); 아직 구현하지 않음                
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