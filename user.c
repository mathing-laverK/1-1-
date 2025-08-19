#include "user.h"
#include <stdio.h>

void user1_init(USER* user1)
{
    printf("=>user1_init function/user.c\n");
    while(1)
    {
        printf("Put your name(playing for WHITE): ");
        if (scanf("%s", user1->name) != 0)
        {
            user1->color = COLOR_WHITE;
            break;
        }
        else
        {
            printf("INVALID NAME! TRY AGAIN");
            continue;
        }
    }
}

void user2_init(USER* user2)
{
    printf("=>user2_init function/user.c\n");
    while(1)
    {
        printf("Put your name(playing for BLACK): ");
        if (scanf("%s", user2->name) != 0)
        {
            user2->color = COLOR_BLACK;
            break;
        }
        else
        {
            printf("INVALID NAME! TRY AGAIN");
            continue;
        }
    }
}
