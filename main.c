#include "header.h"

/* operetions memory */
int ic = IC_INIT;
/* data memory */
int dc = DC_INIT;

register_st r1, r2, r3, r4, r5, r6;



operation operations[OPERATIONS_LENGTH];

int main(int argc, char *argv[])
{
    word wr;
    wr.address = decimal_to_binary_unassigned_base_2(-20);
    printf("%d", wr.address);
    initialize_prog();
    return 1;
}