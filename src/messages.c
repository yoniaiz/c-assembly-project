#include "header.h"
/* fail messages */
#define MEMORY_FAIL "Memory allocation failed!\n"
#define FILE_FAIL "Cannot open file!\n"
#define ARGS_FAIL "Please provide assembly file path!\n"
#define INVALID_COMMAND "Please provide valid "
#define INVALID_OPERATION "assembly command!\n"
#define INVALID_INSTRUCATION "assembly instroction!\n"
#define ENTRY_FAIL "Entry should have a variable!\n"
#define SYMBOL_ERROR "You already declared a label named "
#define INVALID_ADDRESSING "Invalid addressing accrued!\n"

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

void invalid_command(BOOLEAN is_instrucation)
{
    printf(INVALID_COMMAND);
    printf(is_instrucation ? INVALID_INSTRUCATION : INVALID_OPERATION);
    exit(EXIT_FAILURE);
}

void entry_fail()
{
    printf(ENTRY_FAIL);
    exit(EXIT_FAILURE);
}

void symbol_fail(char *label)
{
    printf("%s%s \n", SYMBOL_ERROR, label);
    exit(EXIT_FAILURE);
}

void invalid_addressing()
{
    printf(INVALID_ADDRESSING);
    exit(EXIT_FAILURE);
}

void data_not_found(char *data)
{
    printf("%s Not found!\n", data);
    exit(EXIT_FAILURE);
}