#include "header.h"

static commands extract_command_data(char *str)
{
    commands command;
    int index = 0;
    int strLength = strlen(str);
    char *var1, *var2;

    /* get label if exist from string and add to struct*/
    char *label = (char *)malloc(sizeof(char) * strLength);
    strcpy(label, get_label(str, &index));
    index++;
    if (label)
    {
        command.label = (char *)malloc(sizeof(char) * strlen(label));
        strcpy(command.label, label);
    }
    free(label);

    /* get operation if exist from string and add to struct from last index */
    get_operation(str, &index, &command);

    printf("%s %s %s\n", command.label, command.op.opname, command.instruction);
    return command;
}

void complie_file_input_to_assembly(char **lines)
{
    int i = 0;
    commands cmd[sizeof(lines)];

    while (lines[i])
    {
        extract_command_data(lines[i]);
        i++;
    }

    free(lines);
}