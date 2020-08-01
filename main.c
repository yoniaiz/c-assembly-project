#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st r1, r2, r3, r4, r5, r6;



operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    char *content = 0;

    if(argc == 1)
    {
        printf("Please provide assembly file path!\n");
        exit(EXIT_FAILURE);
    }
    initialize_prog();
    read_file(argv[1], &content);
    free(content);
    return 1;
}