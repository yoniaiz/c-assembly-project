#include "header.h"
/* operetions memory */
extern int ic;
/* data memory */
extern int dc;
extern register_st registers[6];

static commands extract_command_data(char *str)
{
    commands command;
    int index = 0, strLen = strlen(str);
    char *label = (char *)malloc(sizeof(char) * strLen);

    /* initilize the struct */
    command.instruction = (char *)malloc(sizeof(char) * 10);
    command.op.opname = (char *)malloc(sizeof(char) * 10);
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

static void twoLoopsAlgorithm(commands *cmd)
{
    data_row *data = (data_row *)malloc(sizeof(data_row) * 50);
    memory_row *memory = (memory_row *)malloc(sizeof(memory_row) * 50);
    symbol_row *symbol_table = (symbol_row *)malloc(sizeof(symbol_row) * 50);

    if (!data || !memory || !symbol_table)
        memory_allocation_fail();

    first_loop(cmd, &data, &memory, &symbol_table);
    free(cmd);
}

void complie_file_input_to_assembly(char **lines)
{
    int i = 0, commands_count = 0;
    commands *cmd = NULL;

    while (lines[i])
    {
        if (lines[i][0] != ';')
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