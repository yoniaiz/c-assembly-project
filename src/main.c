#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st registers[REGISTERS_AMOUNT];

operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    int i = 1;
    if (argc == 1)
    {
        no_args_fail();
    }

    initialize_prog();
    for (; i < argc; i++)
    {
        char **lines = NULL;
        printf("%s i = %d\n",argv[i], i);
        ic = IC_INIT;
        dc = DC_INIT;
        parse_file_to_array_of_strings(argv[i], &lines);
        complie_file_input_to_assembly(lines);
    }
    return 1;
}