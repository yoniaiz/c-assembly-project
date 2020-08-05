#include "header.h"
#define MAX_LABEL_LENGTH 31

extern operation operations[OPERATIONS_LENGTH];

static int get_operation_from_operations(char *opname)
{
    /* return operation index by comparing strings */
    int i;
    for (i = 0; i < OPERATIONS_LENGTH; i++)
        if (COMP_SIZE(operations[i].opname, opname))
            return i;

    return -1;
}

char *get_label(char *str, int *index)
{
    char *label = NULL;

    while (str[*index] && str[*index] != ':' && *index != MAX_LABEL_LENGTH)
    {
        /* copy characters to and of str or char = ":" (and of label) of index = 31 (max char length) */
        label = realloc(label, sizeof(char) * ((*index) + 1));
        if (!label)
            memory_allocation_fail();

        label[*index] = str[*index];
        (*index)++;
    }

    if (str[*index] != ':' || *index == MAX_LABEL_LENGTH)
    {
        /* label not found free space */
        free(label);
    }
    else
    {
        /* last string char 0 */
        label = realloc(label, sizeof(char) * (*index + 1));
        if (!label)
            memory_allocation_fail();

        label[*index] = 0;
    }

    return label;
}

static int is_valid_instraction(char *str)
{
    return COMP_SIZE(str, DATA) || COMP_SIZE(str, STRING) || COMP_SIZE(str, EXTERN) || COMP_SIZE(str, ENTRY);
}

void get_command(char *str, int *index, commands *cmd)
{
    char *opname = NULL;
    int opindex, i = 1;
    /* check if the command starts with '.' to know its an instruction */
    int isInstruction = str[*index] == '.';

    while (str[*index])
    {
        /* read all laters and allocate dynamicly space untill or instruction is found or assembly operations */
        opname = realloc(opname, sizeof(char) * i);
        if (!opname)
            memory_allocation_fail();

        opname[i - 1] = str[*index];
        opname[i] = 0;

        if (isInstruction && is_valid_instraction(opname))
        {
            /* instoction found. assign to object and set object type to INSTRACTION  */
            cmd->instruction = (char *)malloc(sizeof(char) * i);
            if (!cmd->instruction)
                memory_allocation_fail();

            strcpy(cmd->instruction, opname);
            cmd->command_type = INSTRACTION;
            break;
        }
        else
        {
            opindex = get_operation_from_operations(opname);
            if (opindex > -1)
            {
                /* operation found. assign to object and set object type to EXECUTE  */
                cmd->op.opname = (char *)malloc(sizeof(char) * i);
                if (!cmd->op.opname)
                    memory_allocation_fail();

                strcpy(cmd->op.opname, operations[opindex].opname);
                cmd->op.funct = operations[opindex].funct;
                cmd->op.opcode = operations[opindex].opcode;
                cmd->command_type = EXECUTE;
                break;
            }
        }

        (*index)++;
        i++;
    }

    free(opname);
}

char *get_variable(char *str, int *index, int first_var)
{
    char *var = NULL;
    int i = 1;
    while (str[*index])
    {
        /* iterate on str until: if its first var and found ',' or until and of string */
        if (first_var && str[*index] == ',')
        {
            (*index)++;
            return var;
        }
        var = realloc(var, sizeof(char) * i);
        if (!var)
            memory_allocation_fail();

        var[i - 1] = str[*index];
        var[i] = 0;

        (*index)++;
        i++;
    }

    return var;
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