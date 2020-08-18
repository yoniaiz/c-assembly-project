#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st registers[REGISTERS_AMOUNT];

operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    char **lines = NULL;
    output_files_strs ofs;
    if (argc == 1)
    {
        no_args_fail();
    }

    initialize_prog();
    parse_file_to_array_of_strings(argv[1], &lines);
    ofs = complie_file_input_to_assembly(lines);
    printf("%s \n", ofs.entryF);
    return 1;
}