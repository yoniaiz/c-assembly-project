#include "header.h"

extern operation operations[OPERATIONS_LENGTH];

char *get_label(char *str, int *index)
{
    char *label = NULL;

    while (str[*index] && str[*index] != ':' && *index != 31)
    {
        label = realloc(label, sizeof(char) * (*index));
        if (!label)
            memory_allocation_fail();

        label[*index] = str[*index];
        (*index)++;
    }

    if (str[*index] != ':' || *index == 31)
    {
        free(label);
    }
    else
    {
        /* last string char 0 */
        label = realloc(label, sizeof(char) * (*index));
        if (!label)
            memory_allocation_fail();

        label[*index] = 0;
    }

    return label;
}

static int get_operation_from_operations(char *opname)
{
    int i;
    for (i = 0; i < OPERATIONS_LENGTH; i++)
    {
        if (comp_strings(operations[i].opname, opname))
        {
            return i;
        }
    }

    return -1;
}

static int is_valid_instraction(char *str)
{
    return comp_strings(str, DATA) || comp_strings(str, STRING) || comp_strings(str, EXTERN) || comp_strings(str, ENTRY);
}

void get_operation(char *str, int *index, commands *cmd)
{
    char *opname = NULL;
    int opindex, i = 0;

    if (str[*index] == '.')
    {
        printf("seach for int \n");
        while (str[*index])
        {
            opname = realloc(opname, sizeof(char) * i);
            if (!opname)
                memory_allocation_fail();

            if (is_valid_instraction(opname))
            {
                cmd->instruction = (char *)malloc(sizeof(char) * i);
                cmd->command_type = INSTRACTION;
                break;
            }

            (*index)++;
            i++;
        }
    }
    else
    {
        while (str[*index])
        {
            opname = realloc(opname, sizeof(char) * i);
            if (!opname)
                memory_allocation_fail();

            opname[i] = str[*index];
            opindex = get_operation_from_operations(opname);
            if (opindex > -1)
            {
                /* found operation update in command and status */
                strcpy(cmd->op.opname,operations[opindex].opname);
                cmd->op.funct = operations[opindex].funct;
                cmd->op.opcode = operations[opindex].opcode;

                cmd->command_type = EXECUTE;
                break;
            }

            (*index)++;
            i++;
        }
    }
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
        for (i = 0; num > 0; i++)
        {
            bits[i] = num % 2;
            num = num / 2;
        }

        /* if the original number was negative then change it in complement to 2 shotcut */
        for (i = 0; i < MAX_BIT_SIZE; i++)
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

        for (i = 0; i < MAX_BIT_SIZE; i++)
        {
            /* convert back to number */
            converted_number += bits[i] * pow(2, i);
        }
    }
    else
    {
        /* if number is not negative no need to manupulate */
        return num;
    }

    return converted_number;
}