#include "user.h"
#include <stdio.h>
#include <string.h>


static bool read_token(char* name, size_t max_InputSize, const char* prompt)
{
    if (prompt)
    {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    if (!fgets(name, max_InputSize, stdin))
    {
        name = '\0';
        return false;
    }

    size_t n = strcspn(name, "\r\n");
    name[n] = '\0';
    return true;
}

void user1_init(USER* user1)
{
    printf("=>user1_init function/user.c\n");

    return read_token(&user1->name, sizeof(user1->name), "������ �÷����� ������� �̸��� �Է����ּ���(�ִ� 20��): ");
    /*while (1)
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
    }*/
}

void user2_init(USER* user2)
{
    printf("=>user2_init function/user.c\n");
    return read_token(&user2->name, sizeof(user2->name), "������ �÷����� ������� �̸��� �Է����ּ���(�ִ� 20��): ");

   /* while (1)
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
    }*/
}
