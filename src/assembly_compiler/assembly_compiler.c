#include "header.h"

static void twoLoopsAlgorithm(commands *cmd)
{
    output_files_strs ofs;
    data_row *data = (data_row *)malloc(sizeof(data_row) * 50);
    memory_row *memory = (memory_row *)malloc(sizeof(memory_row) * 50);
    symbol_row *symbol_table = (symbol_row *)malloc(sizeof(symbol_row) * 50);
    /*ofs.objectF = (char *)malloc(sizeof(char) * 50);
    ofs.externalF = (char *)malloc(sizeof(char) * 50);
    ofs.entryF = (char *)malloc(sizeof(char) * 50);*/

    if (!data || !memory || !symbol_table)
        memory_allocation_fail();

    first_loop(cmd, &data, &memory, &symbol_table);
    free(cmd);
    second_loop(memory, symbol_table);

    free(symbol_table);

    printf("%s\n", create_object_file_str(memory, data));
    /*ofs.externalF = create_external_file_str();
    ofs.entryF = create_entry_file_str();*/

    free(data);
    free(memory);
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