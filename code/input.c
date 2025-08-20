#include "input.h"
#include <string.h>
#include <ctype.h>


bool ReadInput_from(INPUT* input)
{

}

static bool read_token(char* input, size_t max_InputSize, const char* prompt)
{
    if (prompt)
    {
        fputs(prompt, stdout);
        fflush(stdout);
    }

    if (!fgets(input, max_InputSize, stdin))
    {
        input = '\0';
        return false;
    }

    size_t n = strcspn(input, "\r\n");
    input[n] = '\0';
    return true;
}

void input_init(INPUT* input)
{
    printf("=>input_init/input.c\n");
    input->For_user_input[0] = '\0';
    input->To_user_input[0] = '\0';
    input->For_row = -1;
    input->For_col = -1;
    input->To_row = -1;
    input->To_col = -1;
    input->is_valid = false;
}

bool is_special(INPUT* input)
{
    printf("=>is_special/input.c\n");
    if (strcmp(input->For_user_input, "O_O_O") == 0 || strcmp(input->For_user_input, "O_O") == 0)
        return true;
    else
        return false;
}

INPUT convert_for_input(INPUT* input)
{   
    printf("=>convert_for_input/input.c\n");
    INPUT isvalid_result;
    isvalid_result.is_valid = false;

    size_t inputlen = strlen(input->For_user_input);
    if (inputlen > 2)
        return isvalid_result;

    char file = input->For_user_input[0];
    char rank = input->For_user_input[1];

    if (file >= 'A' && file <= 'H')
        file += 32;
    else if (!(file >= 'a' && file <= 'h'))
        return isvalid_result;

    if (rank < '1' || rank > '8')
        return isvalid_result;
    
    input->For_row = 8 - (int)(rank - '0');
    input->For_col = (int)file - 'a';
    isvalid_result.is_valid = true;
    return isvalid_result;
}

INPUT convert_to_input(INPUT* input)
{
    printf("=>convert_to_input/input.c\n");
    INPUT isvalid_result;
    isvalid_result.is_valid = false;

    size_t inputlen = strlen(input->To_user_input);
    if (inputlen > 2)
        return isvalid_result;

    char file = input->To_user_input[0];
    char rank = input->To_user_input[1];

    if (file >= 'A' && file <= 'H')
        file += 32;
    else if (!(file >= 'a' && file <= 'h'))
        return isvalid_result;

    if (rank < '1' || rank > '8')
        return isvalid_result;

    input->To_row = 8 - (int)(rank - '0');
    input->To_col = (int)file - 'a';
    isvalid_result.is_valid = true;
    return isvalid_result;
}

bool is_DrawAgree(char* For_user_input)
{
    printf("=>is_DrawAgree/input.c\n");
    if (strcmp(For_user_input, "Draw") == 0)
    {
        return true;
    }
    else
        return false;
}

