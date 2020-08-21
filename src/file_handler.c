#include "header.h"
static void writeFile(char *filename, char *filecontent)
{
    FILE *f;
    if (!(f = fopen(filename, "w")))
    {
        file_fail();
    }

    fputs(filecontent, f);

    fclose(f);
}

static char *filename(char *filename)
{
    static char name[20];
    if (strlen(filename))
        strcpy(name, filename);
    return name;
}

void read_file(char *path, char **content)
{
    FILE *assembly;
    long length;
    filename(path);
    if (!(assembly = fopen(strcat(path, ".txt"), "r")))
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

void writeFiles(output_files_strs ofs)
{
    char name[20];
    strcpy(name, filename(""));

    if (ofs.objectF)
        writeFile(strcat(name, ".obj"), ofs.objectF);
}

/* read the file into a string and split it by enters to create a array of strings without spacess */
void parse_file_to_array_of_strings(char *path, char ***lines)
{
    char *content = NULL;
    read_file(path, &content);
    split_input_by_symbol_and_remove_spaces(content, lines, "\n");
}