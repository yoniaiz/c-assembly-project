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
    char name[20];
    long length;
    
    strcpy(name, filename(path));
    if (!(assembly = fopen(strcat(name, ".as"), "r")))
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
    char fileobj[24];
    char fileext[24];
    char fileent[24];

    if (strlen(ofs.objectF))
    {
        strcpy(fileobj, filename(""));
        writeFile(strcat(fileobj, ".obj"), ofs.objectF);
    }

    if (strlen(ofs.externalF))
    {
        strcpy(fileext, filename(""));
        writeFile(strcat(fileext, ".ext"), ofs.externalF);
    }
    if (strlen(ofs.entryF))
    {
        strcpy(fileent, filename(""));
        writeFile(strcat(fileent, ".ent"), ofs.entryF);
    }

    free(ofs.entryF);
    free(ofs.externalF);
    free(ofs.objectF);
}

/* read the file into a string and split it by enters to create a array of strings without spacess */
void parse_file_to_array_of_strings(char *path, char ****lines)
{
    char *content = NULL;
    read_file(path, &content);
    split_content_by_enters_and_spaces(content, lines);
}