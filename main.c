#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st r1, r2, r3, r4, r5, r6;

operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    char **lines = NULL;

    if (argc == 1)
    {
        no_args_fail();
    }

    initialize_prog();
    parse_file_to_array_of_strings(argv[1], &lines);

    return 1;
}