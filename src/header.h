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
/* instraction types */
#define DATA ".data"
#define STRING ".string"
#define EXTERN ".extern"
#define ENTRY ".entry"

/*addressing types*/
typedef enum
{
    IMMEDIATE_ADDRESSING,
    DIRECT_ADDRESSING,
    RELATIVE_ADDRESSING,
    IMMEDIATE_REGISTER_ADDRESSING
} ADDRESSINGS;

typedef enum
{
    INSTRACTION,
    EXECUTE
} COMMAND_TYPE;

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
} word;

typedef struct op
{
    int opcode;
    int funct;
    char opname[10];
} operation;
typedef struct commands_struct
{
    COMMAND_TYPE command_type;
    char *label;
    operation op;
    char *instruction;
    char *var1;
    char *var2;
} commands;

/* operatios structor */

/* register structor*/
typedef struct st
{
    unsigned int id : 3;
    unsigned int value : MAX_BIT_SIZE;
} register_st;

/* Helpers */
int decimal_to_binary_unassigned_base_2(int decimalnum);
void split_input_by_enters_and_remove_spaces(char *str, char ***lines);
char *get_label(char *str, int *index);
void get_operation(char *str, int *index, commands *cmd);
/* FILE HANDLER */
void parse_file_to_array_of_strings(char *path, char ***lines);
/* INITIALIZERS */
void initialize_prog();
/* Messages */
void memory_allocation_fail();
void file_fail();
void no_args_fail();
/* Assembly compiler */
void complie_file_input_to_assembly(char **lines);