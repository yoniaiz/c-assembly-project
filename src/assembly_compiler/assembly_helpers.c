#include "header.h"

#define CONVER_BIT_FIELD_TO_UNSIGNED_INT(BF) (unsigned int *)(&BF)
#define APPEND_DATA_TO_HEX_CONVERTION(ADDRESS_STR, DATA_ADDRESS, MAIN, DATA, STR_COUNT) \
    sprintf(ADDRESS_STR, "%d", DATA_ADDRESS);                                           \
    COPY_STRING_BY_CHAR(MAIN, ADDRESS_STR, STR_COUNT);                                  \
    MAIN[STR_COUNT++] = '\t';                                                           \
    COPY_STRING_BY_CHAR(MAIN, DATA, STR_COUNT);                                         \
    MAIN[STR_COUNT++] = '\n';

#define MAX_LABEL_LENGTH 31

/* operetions memory */
extern int ic;
/* data memory */
extern int dc;
extern operation operations[OPERATIONS_LENGTH];

static int get_operation_from_operations(char *opname)
{
    /* return operation index by comparing strings */
    int i;
    for (i = 0; i < OPERATIONS_LENGTH; i++)
        if (COMP_STRING(operations[i].opname, opname))
            return i;

    return -1;
}

int get_register(char *var)
{
    int i;
    char regstr[2];
    regstr[0] = 'r';

    if (!var)
        return FALSE;

    for (i = 1; i < REGISTERS_AMOUNT + 1; i++)
    {
        regstr[1] = i + '0';
        if (COMP_STRING(regstr, var))
            return i;
    }

    return FALSE;
}

char *get_label(char *str, int *index)
{
    char *label = NULL;

    while (str[*index] && str[*index] != ':' && *index != MAX_LABEL_LENGTH)
    {
        /* copy characters to and of str or char = ":" (and of label) of index = 31 (max char length) */
        label = realloc(label, sizeof(char) * ((*index) + 1));
        if (!label)
            memory_allocation_fail();

        label[*index] = str[*index];
        (*index)++;
    }

    if (str[*index] != ':' || *index == MAX_LABEL_LENGTH)
    {
        /* label not found free space */
        free(label);
    }
    else
    {
        /* last string char 0 */
        label = realloc(label, sizeof(char) * (*index + 1));
        if (!label)
            memory_allocation_fail();

        label[*index] = 0;
    }

    return label;
}

static int is_valid_instraction(char *str)
{
    return COMP_STRING(str, DATA) || COMP_STRING(str, STRING) || COMP_STRING(str, EXTERN) || COMP_STRING(str, ENTRY);
}

void get_command(char *str, int *index, commands *cmd)
{
    char *opname = NULL;
    int op_index, i = 1;
    /* check if the command starts with '.' to know its an instruction */
    int isInstruction = str[*index] == '.';

    while (str[*index])
    {
        /* read all laters and allocate dynamicly space until or instruction is found or assembly operations */
        opname = realloc(opname, sizeof(char) * i);
        if (!opname)
            memory_allocation_fail();

        opname[i - 1] = str[*index];
        opname[i] = 0;

        if (isInstruction && is_valid_instraction(opname))
        {
            /* instoction found. assign to object and set object type to INSTRACTION  */
            cmd->instruction = (char *)malloc(sizeof(char) * i);
            if (!cmd->instruction)
                memory_allocation_fail();

            strcpy(cmd->instruction, opname);
            cmd->command_type = INSTRACTION;
            (*index)++;
            break;
        }
        else
        {
            op_index = get_operation_from_operations(opname);
            if (op_index > -1)
            {
                /* operation found. assign to object and set object type to EXECUTE  */
                cmd->op.opname = (char *)malloc(sizeof(char) * i);
                if (!cmd->op.opname)
                    memory_allocation_fail();
                strcpy(cmd->op.opname, operations[op_index].opname);
                cmd->op.funct = operations[op_index].funct;
                cmd->op.opcode = operations[op_index].opcode;
                cmd->command_type = EXECUTE;
                (*index)++;
                break;
            }
        }

        (*index)++;
        i++;
    }

    free(opname);
}

char *get_variable(char *str, int *index, int first_var)
{
    char *var = NULL;
    int i = 1;
    while (str[*index])
    {
        /* iterate on str until: if its first var and found ',' or until and of string */
        if (first_var && str[*index] == ',')
        {
            (*index)++;
            return var;
        }
        var = realloc(var, sizeof(char) * i);
        if (!var)
            memory_allocation_fail();

        var[i - 1] = str[*index];
        var[i] = 0;
        (*index)++;
        i++;
    }

    return var;
}

commands extract_command_data(char *str)
{
    commands command;
    int index = 0, strLen = strlen(str);
    char *label = (char *)malloc(sizeof(char) * strLen);

    /* initialize the struct */
    command.instruction = (char *)malloc(sizeof(char) * 10);
    command.op.opname = (char *)malloc(sizeof(char) * 10);
    command.var1 = NULL;
    command.var2 = NULL;

    /* get label if exist from string and add to struct*/
    strcpy(label, get_label(str, &index));
    if (strlen(label))
    {
        index++;
        command.label = (char *)malloc(sizeof(char) * index);
        strcpy(command.label, label);
    }
    else
    {
        /* if no label reset the index */
        command.label = NULL;
        index = 0;
    }

    free(label);

    /* get operation if exist from string and add to struct from last index */
    get_command(str, &index, &command);

    if (strLen != index)
    {
        /* get first var */
        command.var1 = (char *)malloc(sizeof(char) * (strLen - index));
        if (!command.var1)
            memory_allocation_fail();

        strcpy(command.var1, get_variable(str, &index, command.command_type));

        if (index < strLen)
        {
            /* copy var 2 */
            command.var2 = (char *)malloc(sizeof(char) * (strLen - index));
            if (!command.var2)
                memory_allocation_fail();

            strcpy(command.var2, get_variable(str, &index, FALSE));
        }
    }
    return command;
}

typedef struct extra_data_helper
{
    unsigned int type : 3;
    unsigned int data : MAX_BIT_SIZE;
} extra_data_helper;

static char *hex_to_six_chars(char *hex)
{
    int i;
    char *str = (char *)malloc(sizeof(char) * MAX_HEX_SIZE);
    for (i = 0; i < MAX_HEX_SIZE; i++)
    {
        if (i < strlen(hex))
        {
            str[MAX_HEX_SIZE - 1 - i] = hex[strlen(hex) - 1 - i];
        }
        else
        {
            str[MAX_HEX_SIZE - 1 - i] = '0';
        }
    }
    str[i + 1] = 0;
    return str;
}
static char *extra_data_data_to_hex(extra_data data)
{
    int num = data.data;
    char *hex = (char *)malloc(sizeof(char) * 10);
    if (!hex)
        memory_allocation_fail();

    if (data.a)
    {
        num *= 2;
        num += 1;
        num *= 4;
    }
    else if (data.r)
    {
        num *= 4;
        num += 1;
        num *= 2;
    }
    else
    {
        num *= 8;
        num += 1;
    }

    sprintf(hex, "%X", num);
    return hex_to_six_chars(hex);
}
char *create_object_file_str(memory_row *memory, data_row *data)
{
    int data_size = dc, str_count = 0, j;
    int total_size = (ic - IC_INIT) + data_size;
    char data_size_str[10], total_size_str[10], hex[MAX_HEX_SIZE], address[MAX_HEX_SIZE] = {0};
    char *str = (char *)malloc(calculate_total_size_object_file_str_size());
    if (!str)
        memory_allocation_fail();

    sprintf(data_size_str, "%d", data_size);
    sprintf(total_size_str, "%d", total_size);

    str[str_count++] = ' ';
    COPY_STRING_BY_CHAR(str, total_size_str, str_count);

    str[str_count++] = '\t';
    str[str_count++] = ' ';
    COPY_STRING_BY_CHAR(str, data_size_str, str_count);
    str[str_count++] = '\n';
    str[str_count++] = '\n';

    for (j = 0; j < (ic - IC_INIT); j++)
    {
        if (memory[j].address)
        {
            APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].address, str, word_to_hex(CONVER_BIT_FIELD_TO_UNSIGNED_INT(memory[j].wr)), str_count);

            if (memory[j].extra_origin_data.address && (memory[j].extra_origin_data.data || memory[j].extra_origin_data.e))
            {
                APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].extra_origin_data.address, str, extra_data_data_to_hex(memory[j].extra_origin_data), str_count);
            }

            if (memory[j].extra_dest_data.address && memory[j].extra_dest_data.data)
            {
                APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].extra_dest_data.address, str, extra_data_data_to_hex(memory[j].extra_dest_data), str_count);
            }
        }
    }

    for (j = 0; j < dc; j++)
    {
        sprintf(hex, "%X", data[j].data);
        APPEND_DATA_TO_HEX_CONVERTION(address, data[j].address, str, hex_to_six_chars(hex), str_count);
    }

    str[str_count] = 0;
    return str;
}