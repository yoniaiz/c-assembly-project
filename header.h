#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

#define IC_INIT 100
#define DC_INIT 0
#define MAX_BIT_SIZE 24
#define OPERATIONS_LENGTH 16

/* macros */
#define comp_strings(X ,Y) (strcmp(X , Y) == 0 ? TRUE : FALSE )  

/* all assembly commands */
#define MOV "mov"
#define CMP "cmp"
#define ADD "add"
#define SUB "sub"
#define LEA "lea"
#define CLR "clr"
#define NOT "not"
#define INC "inc"
#define DEC "dec"
#define JMP "jmp"
#define BNE "bne"
#define JSR "jsr"
#define RED "red"
#define PRN "prn"
#define RTS "rts"
#define STOP "stop"
/* all assembly commands */


/* cpu work structer */
typedef struct wr {
   unsigned int e: 1;
   unsigned int r: 1;
   unsigned int a: 1;
   unsigned int funct : 5;
   unsigned int dest_register : 3;
   unsigned int dest_addressing : 2;
   unsigned int origin_register : 3;
   unsigned int origin_addressing : 2;
   unsigned int opcode : 6;
} word;

typedef struct op
{
    int op_code;
    int funct;
    char op_name[10];
} operation;


typedef struct st
{
    unsigned int id:3;
    unsigned int value: MAX_BIT_SIZE;
} register_st;

void initialize_prog();