#include "header.h"
/* operetions memory */
extern int ic;
/* data memory */
extern int dc;
extern register_st registers[6];

static void add_to_symbol_table(commands command, symbol_row **symbol_table, int symbols_len, int is_extern)
{
    *symbol_table = (symbol_row *)realloc(*symbol_table, sizeof(symbol_row) * (symbols_len + 1));
    if (!*symbol_table)
        memory_allocation_fail();

    (*symbol_table)[symbols_len].label = (char *)malloc(sizeof(char) * strlen(is_extern ? command.var1 : command.label));
    strcpy((*symbol_table)[symbols_len].label, is_extern ? command.var1 : command.label);
    (*symbol_table)[symbols_len].address = is_extern ? 0 : command.command_type ? ic : dc;
    (*symbol_table)[symbols_len].command_type = command.command_type;
    (*symbol_table)[symbols_len].isExtern = is_extern;
}

static void add_instroction_to_data(commands command, data_row **data)
{
    int i = 0, numstrlen = 0, isstring = FALSE, isdata = FALSE, number = 0, numbers_count = 0;
    char *numstr = (char *)malloc(sizeof(char) * 1);
    int numbers[10];

    while (command.var1[i])
    {
        number = 0;

        if (COMP_STRING(command.instruction, STRING))
        {
            isstring = TRUE;
            if (command.var1[i] != '"')
            {
                *data = (data_row *)realloc(*data, sizeof(data_row) * (dc + 1) * 100);
                if (!*data)
                    memory_allocation_fail();

                (*data)[dc].address = dc;
                (*data)[dc].data = (int)command.var1[i];
                dc++;
            }
        }
        else if (COMP_STRING(command.instruction, DATA))
        {
            isdata = TRUE;
            if (command.var1[i] == ',')
            {
                numstrlen = 0;
                strcpy(numstr, "");
                numbers_count++;
            }
            else
            {
                numstr = (char *)realloc(numstr, sizeof(char) * (++numstrlen));
                numstr[numstrlen - 1] = command.var1[i];
            }

            number = atoi(numstr);
            if (number)
            {
                numbers[numbers_count] = (number);
            }
        }

        i++;
    }

    if (isstring)
    {
        /* last char  in a string is /0 */
        *data = (data_row *)realloc(*data, sizeof(data_row) * (dc));
        if (!*data)
            memory_allocation_fail();

        (*data)[dc].address = dc;
        (*data)[dc].data = 0;
        dc++;
    }

    else if (isdata)
    {

        *data = (data_row *)realloc(*data, sizeof(data_row) * (dc + (numbers_count + 1) * 100));
        if (!*data)
            memory_allocation_fail();

        if (numbers_count == 0)
        {
            (*data)[dc].address = dc;
            (*data)[dc].data = numbers[0];

            dc++;
        }
        else
        {
            for (i = 0; i <= numbers_count; i++)
            {
                (*data)[dc].address = dc;
                (*data)[dc].data = numbers[i];
                if (i != 0)
                {
                    (*data)[dc - i].next = (*data)[dc].address;
                }

                dc++;
            }
        }
    }
}

static ADDRESSINGS get_addressing_method(ADDRESSINGS valid_addressings[], char *var, int reg_idx)
{
    if (var && var[0] == '#')
        return IMMEDIATE_ADDRESSING;
    else if (var && var[0] == '&')
        return RELATIVE_ADDRESSING;
    else if (reg_idx)
        return IMMEDIATE_REGISTER_ADDRESSING;
    else
        return DIRECT_ADDRESSING;
}

static int get_register_val(int reg_idx)
{
    return reg_idx ? registers[reg_idx - 1].id : 0;
}

static word create_word(commands command)
{
    int reg_origin_idx = get_register(command.var1), reg_dest_idx = get_register(command.var2);
    word wr;

    wr.opcode = command.op.opcode;
    wr.origin_addressing = get_addressing_method(command.op.legal_origin_addressing, command.var1, reg_origin_idx);
    wr.origin_register = get_register_val(reg_origin_idx);
    wr.dest_addressing = get_addressing_method(command.op.legal_dest_addressing, command.var2, reg_dest_idx);
    wr.dest_register = get_register_val(reg_dest_idx);
    wr.funct = command.op.funct;
    wr.a = 1;
    wr.e = 0;
    wr.r = 0;
    return wr;
}

static extra_data update_extra_data(ADDRESSINGS addressing, char *var)
{
    extra_data ed;
    ed.data = 0;
    if ((addressing != IMMEDIATE_REGISTER_ADDRESSING) && var)
    {
        if (addressing == IMMEDIATE_ADDRESSING)
            ed.data = (atoi(++var));

        if (addressing == DIRECT_ADDRESSING)
            ed.r = 1;
        else
            ed.a = 1;

        ed.address = ic++;
    }

    return ed;
}

static void add_operation_to_memory(commands command, memory_row **memory)
{
    int current_idx = (ic - IC_INIT);
    *memory = (memory_row *)realloc(*memory, sizeof(memory_row) * (ic + 1));
    if (!*memory)
        memory_allocation_fail();

    (*memory)[current_idx].address = ic++;
    (*memory)[current_idx].cmd = command;
    (*memory)[current_idx].wr = create_word(command);
    (*memory)[current_idx].extra_origin_data = update_extra_data((*memory)[current_idx].wr.origin_addressing, command.var1);
    (*memory)[current_idx].extra_dest_data = update_extra_data((*memory)[current_idx].wr.dest_addressing, command.var2);
}

void first_loop(
    commands *cmd,
    data_row **data,
    memory_row **memory,
    symbol_row **symbol_table)
{
    int i = 0, symbols_length = 0;
    int is_extern = FALSE;
    while (cmd[i].instruction || cmd[i].op.opname)
    {
        is_extern = COMP_STRING(cmd[i].instruction, EXTERN);
        if (cmd[i].label || is_extern)
        {
            add_to_symbol_table(cmd[i], symbol_table, symbols_length, is_extern);
            symbols_length++;
        }

        if (cmd[i].command_type)
        {
            add_operation_to_memory(cmd[i], memory);
        }
        else
        {
            /* handel instruction */
            if (cmd[i].var1 && !is_extern)
            {
                /* handle data and string types  */
                add_instroction_to_data(cmd[i], data);
            }
            else
            {
                /* handle extern and entry types */
            }
        }

        i++;
    }

    for (i = 0; i < dc; i++)
    {
        (*data)[i].address += ic;
    }

    for (i = 0; i < symbols_length; i++)
    {
        /*TODO CHANGE EXTERN TYPE*/
        if ((*symbol_table)[i].command_type == INSTRACTION && !(*symbol_table)[i].isExtern)
        {
            (*symbol_table)[i].address += ic;
        }
    }
}