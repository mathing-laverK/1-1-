#ifndef INPUT_H
#define INPUT_H
#include <stdbool.h>

typedef enum
{
    O_O_O,
    O_O
}CASTILING;

typedef struct INPUT
{
    bool is_valid;
    char For_user_input[20], To_user_input[20];
    int For_row, For_col;
    int To_row, To_col;
}INPUT;

void input_init(INPUT* input);
bool is_special(INPUT* input);
INPUT convert_for_input(INPUT* input);
INPUT convert_to_input(INPUT* input);
bool is_DrawAgree(char* For_user_input);

#endif