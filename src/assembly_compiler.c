#include "header.h"

static commands extract_command_data(char *str)
{
    commands command;
    int index = 0, strLen = strlen(str);
    char *label = (char *)malloc(sizeof(char) * strLen);

    command.instruction = NULL;
    command.op.opname = NULL;
    command.var1 = NULL;
    command.var2 = NULL;

    /* get label if exist from string and add to struct*/
    strcpy(label, get_label(str, &index));

    if (strlen(label))
    {
        index++;
        command.label = (char *)malloc(sizeof(char) * strlen(label));
        strcpy(command.label, label);
    }
    else
    {
        command.label = NULL;
        index = 0;
    }
    free(label);
    /* get operation if exist from string and add to struct from last index */
    get_operation(str, &index, &command);
    index += index < (strLen - 1);

    command.var1 = (char *)malloc(sizeof(char) * (strLen - index));
    if (!command.var1)
        memory_allocation_fail();

    strcpy(command.var1, get_variable(str, &index, TRUE));
    index += index < (strLen - 1);

    if (index < (strLen - 1))
    {
        command.var2 = (char *)malloc(sizeof(char) * (strLen - index));
        if (!command.var2)
            memory_allocation_fail();

        strcpy(command.var2, get_variable(str, &index, FALSE));
    }

    printf("LABEL = %s \t TYPE = %d \n", command.label, command.command_type);
    printf("CMD = %s \t instruction = %s \n", command.op.opname, command.instruction);
    printf("VAR1 = %s \t VAR2 = %s \n", command.var1, command.var2);

    return command;
}

void complie_file_input_to_assembly(char **lines)
{
    int i = 0;
    commands cmd[15];

    while (lines[i])
    {
        cmd[i] = extract_command_data(lines[i]);
        i++;
    }

    free(lines);
}