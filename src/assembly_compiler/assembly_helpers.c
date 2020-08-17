#include "header.h"

#define CONVER_BIT_FIELD_TO_UNSIGNED_INT(BF) (unsigned int *)(&BF)
#define APPEND_DATA_TO_HEX_CONVERTION(ADDRESS_STR, DATA_ADDRESS, MAIN, I, HEX, DATA, STR_COUNT) \
    sprintf(ADDRESS_STR, "%d", DATA_ADDRESS);                                                   \
    COPY_STRING_BY_CHAR(MAIN, ADDRESS_STR, I, STR_COUNT);                                       \
    MAIN[STR_COUNT++] = '\t';                                                                   \
    strcpy(HEX, DATA);                                                                          \
    COPY_STRING_BY_CHAR(MAIN, HEX, I, STR_COUNT);                                               \
    MAIN[STR_COUNT++] = '\n';

#define MAX_LABEL_LENGTH 31
#define MAX_HEX_SIZE 6

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
    int opindex, i = 1;
    /* check if the command starts with '.' to know its an instruction */
    int isInstruction = str[*index] == '.';

    while (str[*index])
    {
        /* read all laters and allocate dynamicly space untill or instruction is found or assembly operations */
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
            break;
        }
        else
        {
            opindex = get_operation_from_operations(opname);
            if (opindex > -1)
            {
                /* operation found. assign to object and set object type to EXECUTE  */
                cmd->op.opname = (char *)malloc(sizeof(char) * i);
                if (!cmd->op.opname)
                    memory_allocation_fail();

                strcpy(cmd->op.opname, operations[opindex].opname);
                cmd->op.funct = operations[opindex].funct;
                cmd->op.opcode = operations[opindex].opcode;
                cmd->command_type = EXECUTE;
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

    /* initilize the struct */
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
    /* skip last later of the command */
    index += index < (strLen - 1);

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

    return command;
}

typedef struct extra_data_helper
{

    unsigned int e : 1;
    unsigned int a : 1;
    unsigned int r : 1;
    unsigned int data : MAX_BIT_SIZE;
} extra_data_helper;

static char *extra_data_data_to_hex(extra_data data)
{
    extra_data_helper rdh;
    rdh.data = data.data;
    printf("DATA = %d\n", data.data);
    printf("DATA = %d\n", rdh.data);
    rdh.a = data.a;
    rdh.e = data.e;
    rdh.r = data.r;
    return word_to_hex(CONVER_BIT_FIELD_TO_UNSIGNED_INT(rdh));
}
char *create_object_file_str(memory_row *memory, data_row *data)
{
    int data_size = dc, str_count = 0, i, j;
    int total_size = (ic - IC_INIT) + data_size;
    char data_size_str[10], total_size_str[10], hex[MAX_HEX_SIZE], address[MAX_HEX_SIZE] = {0};
    char *str = (char *)malloc(sizeof(char) * ((MAX_HEX_SIZE * 2 + 1) * total_size + 1));
    if (!str)
        memory_allocation_fail();

    sprintf(data_size_str, "%d", data_size);
    sprintf(total_size_str, "%d", total_size);

    str[str_count++] = '\t';
    COPY_STRING_BY_CHAR(str, total_size_str, i, str_count);

    str[str_count++] = '\t';
    COPY_STRING_BY_CHAR(str, data_size_str, i, str_count);
    str[str_count++] = '\n';

    for (j = 0; j < (ic - IC_INIT); j++)
    {
        if (memory[j].address)
        {
            APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].address, str, i, hex, word_to_hex(CONVER_BIT_FIELD_TO_UNSIGNED_INT(memory[j].wr)), str_count);

            if (memory[j].extra_origin_data.address && memory[j].extra_origin_data.data)
            {
                APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].extra_origin_data.address, str, i, hex, extra_data_data_to_hex(memory[j].extra_origin_data), str_count);
            }

            if (memory[j].extra_dest_data.address && memory[j].extra_dest_data.data)
            {
                APPEND_DATA_TO_HEX_CONVERTION(address, memory[j].extra_dest_data.address, str, i, hex, extra_data_data_to_hex(memory[j].extra_dest_data), str_count);
            }
        }
    }

    for (j = 0; j < dc; j++)
    {
        sprintf(address, "%d", data[j].address);
        COPY_STRING_BY_CHAR(str, address, i, str_count);
        str[str_count++] = '\t';
        sprintf(hex, "%X", data[j].data);
        COPY_STRING_BY_CHAR(str, hex, i, str_count);
        str[str_count++] = '\n';
    }
    return str;
}