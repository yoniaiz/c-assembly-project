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

int decimal_to_binary_unassigned_base_2(int num)
{
    int converted_number, i = 0;
    int bits[MAX_BIT_SIZE] = {0}, isnegative = num < 0 ? TRUE : FALSE;
    int first_one = FALSE;

    if (isnegative)
    {
        /* convert number from base decimal to base to in array form */
        num = abs(num);
        for (i = MAX_BIT_SIZE; num > 0; i--)
        {
            bits[i] = num % 2;
            num = num / 2;
        }

        /* if the original number was negative then change it in complement to 2 shotcut */
        for (i = MAX_BIT_SIZE; i >= 0; i--)
        {
            /* change all bits to the complement */
            if (first_one)
                bits[i] = bits[i] == 1 ? 0 : 1;

            if (bits[i] == 1 && !first_one)
            {
                /* keep array the same to the first "one" */
                first_one = TRUE;
            }
        }

        for (i = MAX_BIT_SIZE; i >= 0; i--)
        {
            /* convert back to number */
            converted_number += bits[i] * (int)floor(pow(2, (MAX_BIT_SIZE - i)));
        }
    }
    else
    {
        /* if number is not negative no need to manupulate */
        return num;
    }

    return converted_number;
}
