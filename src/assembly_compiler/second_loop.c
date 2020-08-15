#include "header.h"

extern int ic;
/* data memory */
extern int dc;
extern register_st registers[6];

static int get_extra_data_data(ADDRESSINGS addressing, int address, char *var, symbol_row *symbol_table)
{
    int i = 0;
    if (!var)
        return 0;

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

void second_loop(data_row *data, memory_row *memory, symbol_row *symbol_table)
{
    int i;
    for (i = 0; i < (ic - IC_INIT); i++)
    {
        if (memory[i].address)
        {
            if (memory[i].wr.origin_addressing != IMMEDIATE_REGISTER_ADDRESSING && memory[i].wr.origin_addressing != IMMEDIATE_ADDRESSING)
            {
                memory[i].extra_origin_data.data = get_extra_data_data(memory[i].wr.origin_addressing, memory[i].address, memory[i].cmd.var1, symbol_table);
            }
            if (memory[i].wr.dest_addressing != IMMEDIATE_REGISTER_ADDRESSING && memory[i].wr.dest_addressing != IMMEDIATE_ADDRESSING)
            {
                memory[i].extra_dest_data.data = get_extra_data_data(memory[i].wr.dest_addressing, 0, memory[i].cmd.var2, symbol_table);
            }
            printf("var 1 = %s \t var2 = %s \t address %d \t", memory[i].cmd.var1 ,memory[i].cmd.var2, memory[i].address);
            printf("origin %d \t", memory[i].extra_origin_data.data);
            printf("dest %d \n", memory[i].extra_dest_data.data);
        }
    }
}