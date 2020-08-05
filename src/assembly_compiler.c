#include "header.h"

static commands extract_command_data(char *str)
{
    commands command;
    int index = 0;
    int strLength = strlen(str);
    char *var1, *var2;
    command.instruction = NULL;
    command.op.opname = NULL;
    /* get label if exist from string and add to struct*/
    char *label = (char *)malloc(sizeof(char) * strLength);
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

    printf("label = %s\n", command.label);
    if (command.op.opname)
    {
        printf("opname = %s\n", command.op.opname);
    }
    else if (command.instruction)
    {
        printf("instruction = %s\n", command.instruction);
    }

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