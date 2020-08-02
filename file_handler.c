#include "header.h"

void read_file(char *path, char **content)
{
    FILE *assembly;
    long length;

    if (!(assembly = fopen(path, "r")))
    {
        file_fail();
    }

    /* get file length */
    fseek(assembly, 0, SEEK_END);
    length = ftell(assembly);
    fseek(assembly, 0, SEEK_SET);

    *content = (char *)malloc(length * sizeof(char));
    if (!*content)
    {
        memory_allocation_fail();
    }

    /* copy file to string and close file */
    fread(*content, 1, length, assembly);
    fclose(assembly);
}

void parse_input(char *filestring, input_destructor **commands)
{
    int i;
    char **res = NULL;
    input_destructor *arr;
    int columnlen = 0;
    split_input_by_enters_and_remove_spaces(filestring, res);
    
 

    free(res);
}