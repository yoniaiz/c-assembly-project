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

void parse_file_to_array_of_strings(char *path, char ***lines)
{
    char *content = 0;
    read_file(path, &content);
    split_input_by_enters_and_remove_spaces(content, lines);
}