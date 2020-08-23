#include "header.h"
extern int ic;

int calculate_total_size_object_file_str_size()
{
    /* one file line equals to 6 (hex number) * 2 (two numbers) + 1(Tab) * total length */
    return sizeof(char) * ((MAX_HEX_SIZE * 2 + 1) * (ic - IC_INIT) + 1);
}

void split_input_by_symbol(char *str, char ***lines, char *symbol)
{
    char *token = strtok(str, symbol);
    int n_spaces = 0;

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
}

void split_content_by_enters_and_spaces(char *str, char ****lines)
{
    int i = 0, j = 0;
    char **inner = NULL;
    char **line = NULL;

    /* spliting content by enters to array of string */
    split_input_by_symbol(str, &inner, "\n");
    while (inner[i])
    {
        /* spliting the array of string every string by space and assign to lines param to create array of array of strings */
        split_input_by_symbol(inner[i], &line, " ");
        (*lines) = (char ***)realloc(*lines, sizeof(char **) * (i + 1));
        (*lines)[i] = (char **)malloc(sizeof(char *) * 50);
        if (!(*line) || !(*lines)[i])
            memory_allocation_fail();

        while (line[j])
        {
            (*lines)[i][j] = (char *)malloc(sizeof(char) * 20);
            if (!(*lines)[i][j])
                memory_allocation_fail();

            /* assign every string then is spited by space to main array */
            strcpy((*lines)[i][j], line[j]);
            j++;
        }

        j = 0;
        i++;
    }

    (*lines) = (char ***)realloc(*lines, sizeof(char **) * (i + 1));
    (*lines)[i] = NULL;

    free(inner);
    free(line);
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
        /* add every for number to matrix line to simulat hex number */
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
            /* convert every four numbers to hex and add it to string */
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