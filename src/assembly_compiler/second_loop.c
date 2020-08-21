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

static int is_extra_data(int addressing)
{
    return (addressing == DIRECT_ADDRESSING || addressing == RELATIVE_ADDRESSING);
}

static int get_extra_data_data(ADDRESSINGS addressing, int address, char *var, symbol_row *symbol_table)
{
    int i = 0;

    if (addressing == DIRECT_ADDRESSING)
    {
        while (symbol_table[i].label)
        {
            if (COMP_STRING(symbol_table[i].label, var))
                return symbol_table[i].address;
            i++;
        }
    }
    else if (addressing == RELATIVE_ADDRESSING)
    {
        while (symbol_table[i].label)
        {
            if (COMP_STRING(symbol_table[i].label, (var + 1)))
                return (symbol_table[i].address - address);
            i++;
        }
    }

    return 0;
}

void second_loop(memory_row *memory, symbol_row *symbol_table)
{
    int i;
    for (i = 0; i < (ic - IC_INIT); i++)
    {
        /* complete the memory missing data */
        if (memory[i].address)
        {
            if (is_extra_data(memory[i].wr.origin_addressing))
            {
                memory[i].extra_origin_data.data = get_extra_data_data(memory[i].wr.origin_addressing, memory[i].address, memory[i].cmd.var1, symbol_table);
                printf("%d\n", memory[i].extra_origin_data.data);
                UPDATE_ADDRESS_IF_EXTERN(memory[i].extra_origin_data);
            }
            if (is_extra_data(memory[i].wr.dest_addressing))
            {
                memory[i].extra_dest_data.data = get_extra_data_data(memory[i].wr.dest_addressing, 0, memory[i].cmd.var2, symbol_table);
                UPDATE_ADDRESS_IF_EXTERN(memory[i].extra_dest_data);
            }
        }
    }
}