#include "header.h"
/* fail messages */
#define MEMORY_FAIL "Memory allocation failed!\n"
#define FILE_FAIL "Cannot open file!\n"
#define ARGS_FAIL "Please provide assembly file path!\n"

void memory_allocation_fail()
{
    printf(MEMORY_FAIL);
    exit(EXIT_FAILURE);
}

void file_fail()
{
    printf(FILE_FAIL);
    exit(EXIT_FAILURE);
}

void no_args_fail()
{
    printf(ARGS_FAIL);
    exit(EXIT_FAILURE);
}