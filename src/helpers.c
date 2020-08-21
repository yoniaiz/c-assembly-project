#include "header.h"
extern int ic;

int calculate_total_size_object_file_str_size()
{
    return sizeof(char) * ((MAX_HEX_SIZE * 2 + 1) * (ic - IC_INIT) + 1);
}
void remove_spaces(char *str_with_spaces)
{
    int length, i = 0, j = 0;
    char *str_without_spaces;

    length = strlen(str_with_spaces);
    str_without_spaces = (char *)malloc(length + 1);
    if (!str_without_spaces)
    {
        memory_allocation_fail();
    }
    while (*(str_with_spaces + i))
    {
        /* remove all white spaces from the string */
        if (!(*(str_with_spaces + i) == ' '))
        {
            *(str_without_spaces + j) = *(str_with_spaces + i);
            j++;
        }
        i++;
    }
    /* last string char 0 */
    *(str_without_spaces + j) = 0;
    /* update string after removing spaces */
    strcpy(str_with_spaces, str_without_spaces);
}

void split_input_by_symbol_and_remove_spaces(char *str, char ***lines, char *symbol)
{
    char *token = strtok(str, symbol);
    int n_spaces = 0, i;

    /* split string and append tokens to 'res' */
    while (token)
    {
        *lines = realloc(*lines, sizeof(char *) * ++n_spaces);

        if (!lines)
            memory_allocation_fail();

        (*lines)[n_spaces - 1] = token;

        token = strtok(NULL, symbol);
    }

    /* realloc one extra element for the last NULL */
    *lines = realloc(*lines, sizeof(char *) * (n_spaces + 1));
    (*lines)[n_spaces] = 0;

    for (i = 0; i < n_spaces; i++)
    {
        /* remove spaces from all array items */
        if ((*lines)[i])
        {
            remove_spaces((*lines)[i]);
        }
    }
}

char *word_to_hex(unsigned int *p)
{
    int i = 0, j = 0, k = 3, hex = 0;
    char *hexstr = (char *)malloc(sizeof(char) * 1);
    char *totalhexstr = (char *)malloc(sizeof(char) * 7);
    int bitsMatrix[6][4];

    if (!hexstr || !totalhexstr)
        memory_allocation_fail();

    for (i = 0; i < (MAX_BIT_SIZE + 3); i++)
    {
        if (i != 0 && i % 4 == 0)
        {
            k = 3;
            j++;
        }

        bitsMatrix[j][k--] = (((*p) >> i) & 1);
    }

    for (i = 5; i >= 0; i--)
    {
        for (k = 3; k >= 0; k--)
        {
            hex = (hex << 1) | bitsMatrix[i][k];
        }
        sprintf(hexstr, "%X", hex);
        hex = 0;
        if (i == 5)
            strcpy(totalhexstr, hexstr);
        else
            strcat(totalhexstr, hexstr);
    }
    totalhexstr[6] = 0;

    return totalhexstr;
}