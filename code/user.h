#ifndef USER_H
#define USER_H

#include "color.h"

typedef struct {
    char name[20];
    COLOR color;
    int time_left;
}USER;

void user1_init(USER* user1);
void user2_init(USER* user2);

#endif //user.h