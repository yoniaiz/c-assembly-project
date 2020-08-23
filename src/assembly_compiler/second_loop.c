#include "header.h"

#define UPDATE_ADDRESS_IF_EXTERN(ADDRESS) \
    if (ADDRESS.data == 0)                \
    {                                     \
        ADDRESS.a = 0;                    \
        ADDRESS.r = 0;                    \
        ADDRESS.e = 1;                    \
    }
extern int ic;
/* data memory */
extern int dc;
extern register_st registers[6];

static int handle_relative_addressing_extra_data(char *var, int address, symbol_row *symbol_table)
{
    int i = 0;
    while (symbol_table[i].label)
    {
        if (COMP_STRING(symbol_table[i].label, (var + 1)))
            return (symbol_table[i].address - address);
        i++;
    }

    data_not_found(var);
    return -1;
}

static int handle_direct_addressing_extra_data(char *var, symbol_row *symbol_table)
{
    int i = 0;
    while (symbol_table[i].label)
    {
        if (COMP_STRING(symbol_table[i].label, var))
            return symbol_table[i].address;
        i++;
    }

    data_not_found(var);
    return -1;
}

void second_loop(memory_row *memory, symbol_row *symbol_table)
{
    int i;
    for (i = 0; i < (ic - IC_INIT); i++)
    {
        /* complete the memory missing data */
        if (memory[i].address)
        {
            if (memory[i].wr.origin_addressing == DIRECT_ADDRESSING)
            {
                memory[i].extra_origin_data.data = handle_direct_addressing_extra_data(memory[i].cmd.var1, symbol_table);
                UPDATE_ADDRESS_IF_EXTERN(memory[i].extra_origin_data);
            }

            if (memory[i].wr.dest_addressing == DIRECT_ADDRESSING)
            {
                memory[i].extra_dest_data.data = handle_direct_addressing_extra_data(memory[i].cmd.var2, symbol_table);
                UPDATE_ADDRESS_IF_EXTERN(memory[i].extra_origin_data);
            }
            else if (memory[i].wr.dest_addressing == RELATIVE_ADDRESSING)
            {
                memory[i].extra_dest_data.data = handle_relative_addressing_extra_data(memory[i].cmd.var2, memory[i].address, symbol_table);
            }
        }
    }
}