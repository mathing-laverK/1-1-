#ifndef MOVELOG_H
#define MOVELOG_H

typedef struct MoveLog{
    char move[20];
    struct MoveLog* next;
} MoveLog;

void make_history_MOVE();
#endif
