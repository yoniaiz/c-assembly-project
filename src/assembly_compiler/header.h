#include "../header.h"

typedef struct extra_data
{
    unsigned int e : 1;
    unsigned int r : 1;
    unsigned int a : 1;
    unsigned int data : MAX_BIT_SIZE;
    int address;
} extra_data;
typedef struct memory
{
    unsigned int address : MAX_BIT_SIZE;
    word wr;
    commands cmd;
    extra_data extra_dest_data;
    extra_data extra_origin_data;
} memory_row;

typedef struct data
{
    int address;
    unsigned int data : MAX_BIT_SIZE;
    unsigned int next : MAX_BIT_SIZE;
} data_row;

typedef struct symbol
{
    char *label;
    unsigned int address : MAX_BIT_SIZE;
    COMMAND_TYPE command_type;
    BOOLEAN isExtern;
} symbol_row;

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