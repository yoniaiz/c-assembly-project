
#include "header.h"

extern register_st r1, r2, r3, r4, r5, r6;
extern operation operations[OPERATIONS_LENGTH];

static operation create_op(
    int code,
    int funct,
    char *name,
    ADDRESSINGS legal_dest_addresing[3],
    ADDRESSINGS legal_origin_addresing[3])
{
    int i;
    operation new_operation;
    new_operation.opcode = code;
    new_operation.funct = funct;
    new_operation.opname = (char *)malloc(sizeof(char) * strlen(name));
    if (!new_operation.opname)
        memory_allocation_fail();

    strcpy(new_operation.opname, name);

    for (i = 0; i < 3; i++)
    {
        new_operation.legal_dest_addressing[i] = legal_dest_addresing ? legal_dest_addresing[i] : -1;
        new_operation.legal_origin_addressing[i] = legal_origin_addresing ? legal_origin_addresing[i] : -1;
    }
    return new_operation;
}

static void initialize_registers()
{
    r1.id = 1;
    r1.value = 0;
    r2.id = 2;
    r2.value = 0;
    r3.id = 3;
    r3.value = 0;
    r4.id = 4;
    r4.value = 0;
    r5.id = 5;
    r5.value = 0;
    r6.id = 1;
    r6.value = 0;
}

static void initialize_operations()
{
    ADDRESSINGS di[3] = {DIRECT_ADDRESSING, IMMEDIATE_REGISTER_ADDRESSING, -1};
    ADDRESSINGS dii[3] = {DIRECT_ADDRESSING, IMMEDIATE_ADDRESSING, IMMEDIATE_REGISTER_ADDRESSING};
    ADDRESSINGS d[3] = {DIRECT_ADDRESSING, -1, -1};
    ADDRESSINGS dr[3] = {DIRECT_ADDRESSING, RELATIVE_ADDRESSING, -1};

    /* creating the operations table */
    operations[0] = create_op(0, 0, MOV, di, dii);
    operations[1] = create_op(1, 0, CMP, dii, dii);
    operations[2] = create_op(2, 1, ADD, di, dii);
    operations[3] = create_op(2, 2, SUB, di, dii);
    operations[4] = create_op(4, 0, LEA, di, d);
    operations[5] = create_op(5, 1, CLR, di, NULL);
    operations[6] = create_op(5, 2, NOT, di, NULL);
    operations[7] = create_op(5, 3, INC, di, NULL);
    operations[8] = create_op(5, 4, DEC, di, NULL);
    operations[9] = create_op(9, 1, JMP, dr, NULL);
    operations[10] = create_op(9, 2, BNE, dr, NULL);
    operations[11] = create_op(9, 3, JSR, dr, NULL);
    operations[12] = create_op(12, 0, RED, di, NULL);
    operations[13] = create_op(13, 0, PRN, dii, NULL);
    operations[14] = create_op(14, 0, RTS, NULL, NULL);
    operations[15] = create_op(15, 0, STOP, NULL, NULL);
}

void initialize_prog()
{
    initialize_registers();
    initialize_operations();
}