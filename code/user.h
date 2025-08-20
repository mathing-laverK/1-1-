#ifndef USER_H
#define USER_H

#include "color.h"
#include <stdbool.h>

typedef struct {
    char name[20];
    COLOR color;
    int time_left;
}USER;

void user1_init(USER* user1);
void user2_init(USER* user2);
static bool read_token(char* name, size_t max_InputSize, const char* prompt);

#endif //user.h