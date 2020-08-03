#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define MAX_BIT_SIZE 24
#define OPERATIONS_LENGTH 16

#define IC_INIT 100
#define DC_INIT 0

/* macros */
#define comp_strings(X, Y) (strcmp(X, Y) == 0 ? TRUE : FALSE)

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

/*addressing types*/
#define IMMEDIATE_ADDRESSING 0
#define DIRECT_ADDRESSING 1
#define RELATIVE_ADDRESSING 2
#define IMMEDIATE_REGISTER_ADDRESSING 3

/* cpu word structer */
typedef struct wr
{
    unsigned int e : 1;
    unsigned int r : 1;
    unsigned int a : 1;
    unsigned int funct : 5;
    unsigned int dest_register : 3;
    unsigned int dest_addressing : 2;
    unsigned int origin_register : 3;
    unsigned int origin_addressing : 2;
    unsigned int opcode : 6;
    unsigned int extra_dest_data : 21;
    unsigned int extra_dest_e : 1;
    unsigned int extra_dest_r : 1;
    unsigned int extra_dest_a : 1;
    unsigned int extra_origin_data : 21;
    unsigned int extra_origin_e : 1;
    unsigned int extra_origin_r : 1;
    unsigned int extra_origin_a : 1;
} main_parsed_word;

typedef struct input_struct
{
    char *label;
    char *operation;
    char *var1;
    char *var2;
} input_destructor;

/* operatios structor */
typedef struct op
{
    int opcode;
    int funct;
    char opname[10];
} operation;

/* register structor*/
typedef struct st
{
    unsigned int id : 3;
    unsigned int value : MAX_BIT_SIZE;
} register_st;

/* Helpers */
int decimal_to_binary_unassigned_base_2(int decimalnum);
void split_input_by_enters_and_remove_spaces(char *str, char ***lines);
/* FILE HANDLER */
void parse_file_to_array_of_strings(char *path, char ***lines);
/* INITIALIZERS */
void initialize_prog();
/* Messages */
void memory_allocation_fail();
void file_fail();
void no_args_fail();