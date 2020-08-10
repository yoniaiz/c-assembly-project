#include "header.h"

/* operetions memory */
extern int ic;
/* data memory */
extern int dc;

static commands extract_command_data(char *str)
{
    commands command;
    int index = 0, strLen = strlen(str);
    char *label = (char *)malloc(sizeof(char) * strLen);

    /* initilize the struct */
    command.instruction = NULL;
    command.op.opname = NULL;
    command.var1 = NULL;
    command.var2 = NULL;

    /* get label if exist from string and add to struct*/
    strcpy(label, get_label(str, &index));
    if (strlen(label))
    {
        index++;
        command.label = (char *)malloc(sizeof(char) * index);
        strcpy(command.label, label);
    }
    else
    {
        /* if no label reset the index */
        command.label = NULL;
        index = 0;
    }

    free(label);

    /* get operation if exist from string and add to struct from last index */
    get_command(str, &index, &command);
    /* skip last later of the command */
    index += index < (strLen - 1);

    /* get first var */
    command.var1 = (char *)malloc(sizeof(char) * (strLen - index));
    if (!command.var1)
        memory_allocation_fail();

    strcpy(command.var1, get_variable(str, &index, command.command_type));

    if (index < (strLen - 1))
    {
        /* copy var 2 */
        command.var2 = (char *)malloc(sizeof(char) * (strLen - index));
        if (!command.var2)
            memory_allocation_fail();

        strcpy(command.var2, get_variable(str, &index, FALSE));
    }

    return command;
}

static void add_instroction_to_symbol_table(commands command, symbol_row **symbol_table, int *symbols_len)
{
    *symbol_table = (symbol_row *)realloc(*symbol_table, sizeof(symbol_row) * ((*symbols_len) + 1));
    if (!*symbol_table)
        memory_allocation_fail();

    (*symbol_table)[*symbols_len].label = (char *)malloc(sizeof(char) * strlen(command.label));
    strcpy((*symbol_table)[*symbols_len].label, command.label);
    (*symbol_table)[*symbols_len].address = dc;
    (*symbol_table)[*symbols_len].command_type = command.command_type;
    (*symbol_table)[*symbols_len].isExtern = COMP_STRING(command.instruction, EXTERN);
    (*symbols_len)++;
}

static void add_instroction_to_data(commands command, data_row **data)
{
    int i = 0, numstrlen = 0, isstring = FALSE, prev_dc = 0, numbers_count = 0;
    char *numstr = (char *)malloc(sizeof(char) * 1);
    int numbers[10];

    while (command.var1[i])
    {
        if (COMP_STRING(command.instruction, STRING))
        {
            isstring = TRUE;
            if (command.var1[i] != '"')
            {
                *data = (data_row *)realloc(*data, sizeof(data_row) * (dc + 1));
                if (!*data)
                    memory_allocation_fail();

                (*data)[dc].address = dc;
                (*data)[dc].data = (int)command.var1[i];
                dc++;
            }
        }
        else
        {
            if (command.var1[i] == ',')
            {
                numstrlen = 0;
                strcpy(numstr, "");
                numbers_count++;
            }
            else
            {
                numstr = (char *)realloc(numstr, sizeof(char) * (++numstrlen));
                numstr[numstrlen - 1] = command.var1[i];
            }

            int number = atoi(numstr);
            if (number)
            {
                /*TODO work on the complement to 2 function*/
                numbers[numbers_count] = number;
            }
        }

        i++;
    }

    if (isstring)
    {
        /* last char  in a string is /0 */
        *data = (data_row *)realloc(*data, sizeof(data_row) * (dc));
        if (!*data)
            memory_allocation_fail();

        (*data)[dc].address = dc;
        (*data)[dc].data = 0;
        dc++;
    }

    else
    {

        *data = (data_row *)realloc(*data, sizeof(data_row) * (dc + (numbers_count + 2) * 10));
        if (!*data)
            memory_allocation_fail();

        for (i = 0; i <= numbers_count; i++)
        {

            (*data)[dc].address = dc;
            (*data)[dc].data = numbers[i];

            dc++;
        }
    }
}

static void first_loop(
    commands *cmd,
    data_row **data,
    memory_row **memory,
    symbol_row **symbol_table)
{
    int i = 0, symbols_length = 0, islabel;

    while (cmd[i].instruction || cmd[i].op.opname)
    {
        islabel = cmd[i].label ? 1 : 0;
        if (!cmd[i].command_type && cmd[i].var1)
        {
            if (islabel)
            {
                add_instroction_to_symbol_table(cmd[i], symbol_table, &symbols_length);
            }

            add_instroction_to_data(cmd[i], data);
        }
        else
        {
        }

        i++;
    }

    for (i = 0; i < dc; i++)
    {
        printf("%d\n", (*data)[i].data);
    }

    for (i = 0; i < symbols_length; i++)
    {
        printf("%s\n", (*symbol_table)[i].label);
    }
}

static void twoLoopsAlgorithm(commands *cmd)
{
    data_row *data = (data_row *)malloc(sizeof(data_row) * 5);
    memory_row *memory = (memory_row *)malloc(sizeof(memory_row) * 5);
    symbol_row *symbol_table = NULL;
    first_loop(cmd, &data, &memory, &symbol_table);
    free(cmd);
}

void complie_file_input_to_assembly(char **lines)
{
    int i = 0, commands_count = 0;
    commands *cmd = NULL;

    while (lines[i])
    {
        if (lines[i][0] != '#')
        {
            cmd = (commands *)realloc(cmd, sizeof(commands) * (commands_count + 1));
            if (!cmd)
            {
                memory_allocation_fail();
            }
            cmd[commands_count] = extract_command_data(lines[i]);
            commands_count++;
        }
        i++;
    }

    free(lines);

    twoLoopsAlgorithm(cmd);
}