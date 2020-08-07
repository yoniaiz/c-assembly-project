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

    strcpy(command.var1, get_variable(str, &index, TRUE));

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
    int prev_item = *symbols_len;
    *symbol_table = (symbol_row *)realloc(*symbol_table, sizeof(symbol_row *) * (prev_item + 1));
    if (!(*symbol_table))
        memory_allocation_fail();

    symbol_table[prev_item]->label = (char *)malloc(sizeof(char) * strlen(command.label));
    strcpy(symbol_table[prev_item]->label, command.label);
    symbol_table[prev_item]->address = dc;
    symbol_table[prev_item]->command_type = command.command_type;
    symbol_table[prev_item]->isExtern = COMP_STRING(command.instruction, EXTERN);
    (*symbols_len)++;
}

static void add_instroction_to_data(commands command, data_row **data)
{
    int i;

    if (COMP_STRING(command.instruction, STRING))
    {
        for (i = 0; i < strlen(command.var1); i++)
        {
            if (command.var1[i] != '"')
            {
                *data = (data_row *)realloc(*data, sizeof(data_row *) * (dc + 1));
                if (!*data)
                    memory_allocation_fail();

                data[dc] = (data_row *)malloc(sizeof(data_row) * 1);
                if (!data[dc])
                    memory_allocation_fail();

                data[dc]->address = dc;
                data[dc]->data = (int)command.var1[i];
                dc++;
            }
        }
    }
    else
    {
        *data = (data_row *)realloc(*data, sizeof(data_row) * (dc + 1));
        if (!*data)
            memory_allocation_fail();

        data[dc] = (data_row *)malloc(sizeof(data_row) * 1);
        if (!data[dc])
            memory_allocation_fail();
        data[dc]->address = dc;
        data[dc]->data = decimal_to_binary_unassigned_base_2(atoi(command.var1));

        dc++;
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
        if (!cmd[i].command_type)
        {
            if (islabel)
                add_instroction_to_symbol_table(cmd[i], symbol_table, &symbols_length);

            add_instroction_to_data(cmd[i], data);
        }
        i++;
    }
}

static void twoLoopsAlgorithm(commands *cmd)
{
    data_row *data = NULL;
    memory_row *memory = NULL;
    symbol_row *symbol_table = NULL;
    first_loop(cmd, &data, &memory, &symbol_table);
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