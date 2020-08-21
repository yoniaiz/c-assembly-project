#include "header.h"

static void twoLoopsAlgorithm(commands *cmd)
{
    output_files_strs ofs;
    data_row *data = (data_row *)malloc(sizeof(data_row) * 50);
    memory_row *memory = (memory_row *)malloc(sizeof(memory_row) * 50);
    symbol_row *symbol_table = (symbol_row *)malloc(sizeof(symbol_row) * 40);

    if (!data || !memory || !symbol_table)
        memory_allocation_fail();

    /*Two loop assembly compile algorithm*/
    first_loop(cmd, &data, &memory, &symbol_table);
    second_loop(memory, symbol_table);
    free(cmd);
    free(symbol_table);

    /* get parsed assembly to hex code to write to files */
    ofs.objectF = (char *)malloc(calculate_total_size_object_file_str_size());
    if (!ofs.objectF)
        memory_allocation_fail();

    strcpy(ofs.objectF, create_object_file_str(memory, data));
    /*ofs.externalF = create_external_file_str();
    ofs.entryF = create_entry_file_str();*/
    free(data);
    writeFiles(ofs);
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