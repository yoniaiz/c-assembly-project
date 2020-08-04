#include "header.h"

commands extract_command_data(char *str)
{
    
}

void complie_file_input_to_assembly(char **lines)
{
    int i = 0;
    commands cmd[sizeof(lines)];

    while (lines[i])
    {
        cmd[i] = extract_command_data(lines[i]);
    }
}