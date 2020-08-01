#include "header.h"

void read_file(char *path, char **content)
{
    FILE *assembly;
    long length;

    if (!(assembly = fopen(path, "r")))
    {
        fprintf(stderr, "Cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    fseek(assembly, 0, SEEK_END);
    length = ftell(assembly);
    fseek(assembly, 0, SEEK_SET);
    *content = (char *) malloc(length * sizeof(char));
    if (!*content)
    {
        printf("failed to allocate memory! \n");
        exit(EXIT_FAILURE);
    }

    fread(*content, 1, length, assembly);
    fclose(assembly);
}