#include "header.h"
#define FILE_NAME_SIZE 20
#define FILE_NAME_WITH_TYPE_SIZE 24

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
    static char name[FILE_NAME_SIZE];
    if (strlen(filename))
        strcpy(name, filename);
    return name;
}

void read_file(char *path, char **content)
{
    FILE *assembly;
    char name[FILE_NAME_SIZE];
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

    *content = (char *)calloc(length, sizeof(char));
    if (!*content)
    {
        memory_allocation_fail();
    }

    /* copy file to string and close file */
    fread(*content, sizeof(char), length, assembly);
    fclose(assembly);
}

void writeFiles(output_files_strs ofs)
{
    if (strlen(ofs.objectF))
    {
        char file[FILE_NAME_WITH_TYPE_SIZE];
        strcpy(file, filename(""));
        writeFile(strcat(file, ".obj"), ofs.objectF);
    }

    if (strlen(ofs.externalF))
    {
        char file[FILE_NAME_WITH_TYPE_SIZE];
        strcpy(file, filename(""));
        writeFile(strcat(file, ".ext"), ofs.externalF);
    }
    if (strlen(ofs.entryF))
    {
        char file[FILE_NAME_WITH_TYPE_SIZE];
        strcpy(file, filename(""));
        writeFile(strcat(file, ".ent"), ofs.entryF);
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
    free(content);
}