#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st r1, r2, r3, r4, r5, r6;

operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    int i;
    char *content = 0;
    input_destructor *commands = NULL;

    if (argc == 1)
    {
        no_args_fail();
    }

    initialize_prog();
    read_file(argv[1], &content);
    parse_input(content, &commands);

    return 1;
}