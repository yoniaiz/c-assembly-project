#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAX_BIT_SIZE 21
#define OPERATIONS_LENGTH 16
#define REGISTERS_AMOUNT 6

#define IC_INIT 100
#define DC_INIT 0

/* macros */
#define COMP_STRING(X, Y) (strcmp(X, Y) == 0 ? TRUE : FALSE)
#define MATRIX_SIZE(a) (sizeof(a) / sizeof(a[0]))
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

typedef enum
{
    FALSE,
    TRUE
} BOOLEAN;

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

typedef struct extra_data
{
    unsigned int e : 1;
    unsigned int r : 1;
    unsigned int a : 1;
    unsigned int data : MAX_BIT_SIZE;
    int address;
} extra_data;

/* assembly basic operation with funct and code */
typedef struct op
{
    int opcode;
    int funct;
    char *opname;
    ADDRESSINGS legal_dest_addressing[3];
    ADDRESSINGS legal_origin_addressing[3];
} operation;

/* command after parsing the file */
typedef struct commands_struct
{
    COMMAND_TYPE command_type;
    operation op;
    char *label;
    char *instruction;
    char *var1;
    char *var2;
} commands;

typedef struct memory
{
    unsigned int address : MAX_BIT_SIZE;
    word wr;
    commands cmd;
    extra_data extra_dest_data;
    extra_data extra_origin_data;
} memory_row;

typedef struct data
{
    unsigned int address : MAX_BIT_SIZE;
    unsigned int data : MAX_BIT_SIZE;
    unsigned int next : MAX_BIT_SIZE;
} data_row;

typedef struct symbol
{
    char *label;
    unsigned int address : MAX_BIT_SIZE;
    COMMAND_TYPE command_type;
    BOOLEAN isExtern;
} symbol_row;

typedef struct files
{
    char *objectF;
    char *externalF;
    char *entryF;
} output_files_strs;

/* register structor*/
typedef struct st
{
    unsigned int id : 3;
    unsigned int value : MAX_BIT_SIZE;
} register_st;

/* Helpers */
int decimal_to_binary_unassigned_base_2(int decimalnum);
int decimal_to_hex(int num);
char *word_to_hex(word wr);
void split_input_by_enters_and_remove_spaces(char *str, char ***lines);
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
