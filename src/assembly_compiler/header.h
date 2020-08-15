#include "../header.h"

/* Main Logic */
void first_loop(
    commands *cmd,
    data_row **data,
    memory_row **memory,
    symbol_row **symbol_table);

void second_loop(memory_row *memory, symbol_row *symbol_table);

/* helpers */
commands extract_command_data(char *str);
char *get_label(char *str, int *index);
void get_command(char *str, int *index, commands *cmd);
char *get_variable(char *str, int *index, int first_var);
int get_register(char *var);
char *create_object_file_str(memory_row *memory, data_row *data);