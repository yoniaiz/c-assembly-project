
#include "header.h"

extern register_st r1, r2, r3, r4, r5, r6;
extern operation operations[OPERATIONS_LENGTH];

static operation create_op(int code, int funct, char *name)
{
    operation new_operation;
    new_operation.opcode = code;
    new_operation.funct = funct;
    new_operation.opname = (char *)malloc(sizeof(char) * strlen(name));
    if(!new_operation.opname)
        memory_allocation_fail();
        
    strcpy(new_operation.opname, name);
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
    /* creating the operations table */
    operations[0] = create_op(0, 0, MOV);
    operations[1] = create_op(1, 0, CMP);
    operations[2] = create_op(2, 1, ADD);
    operations[3] = create_op(2, 2, SUB);
    operations[4] = create_op(4, 0, LEA);
    operations[5] = create_op(5, 1, CLR);
    operations[6] = create_op(5, 2, NOT);
    operations[7] = create_op(5, 3, INC);
    operations[8] = create_op(5, 4, DEC);
    operations[9] = create_op(9, 1, JMP);
    operations[10] = create_op(9, 2, BNE);
    operations[11] = create_op(9, 3, JSR);
    operations[12] = create_op(12, 0, RED);
    operations[13] = create_op(13, 0, PRN);
    operations[14] = create_op(14, 0, RTS);
    operations[15] = create_op(15, 0, STOP);
}

void initialize_prog()
{
    initialize_registers();
    initialize_operations();
}