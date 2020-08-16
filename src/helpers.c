#include "header.h"

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

void split_input_by_enters_and_remove_spaces(char *str, char ***lines)
{
    char *token = strtok(str, "\n");
    int n_spaces = 0, i;

    /* split string and append tokens to 'res' */
    while (token)
    {
        *lines = realloc(*lines, sizeof(char *) * ++n_spaces);

        if (!lines)
            memory_allocation_fail();

        (*lines)[n_spaces - 1] = token;

        token = strtok(NULL, "\n");
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

char *word_to_hex(word wr)
{
    int i = 0, j = 0, k = 3, hex = 0;
    unsigned int *p = (unsigned int *)(&wr);
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