/*
 * This library contains methods to manipulate files
 *
 * Author: Quemuel Alves Nassor
 * Date: 23/07/21
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\file.h"
#elif defined(__unix__)
#include "../include/file.h"
#endif

const char* FILE_HANDLERS[] = { "r", "r+", "rb", "rb+", "w", "w+", "wb", "wb+", "a", "a+", "ab", "ab+" };

/*
 * Function to test file access
 * parameter: mode, open file mode
 * parameter: path, path plus file name
 * return: opened file pointer or null
 */
FILE* test_open(int mode, char* file_path)
{
    if ((int)strlen(file_path) == 0 || file_path == NULL)
    {
        errno = EINVAL;
        perror("The file path entered is invalid");
        return NULL;
    }

    char* filename = &strrchr(file_path, DIR_SEPARATOR_CHR)[1];
    FILE* file_pointer = fopen(file_path, FILE_HANDLERS[mode]);
    char* msg = error_mess("Unable to open file", filename);

    if (file_pointer == NULL)
    {
        perror(msg);
        free(msg);
    }

    return file_pointer;
}

/*
 * Function to get file size
 * parameter: file_path, path plus file name
 * return: size of file or zero
 */
long get_file_size(char* file_path)
{
    FILE* file_pointer = test_open(READ, file_path);
    if (file_pointer == NULL)
    {
        return 0;
    }

    fseek(file_pointer, START_OF_FILE, SEEK_END);   /* scroll through the file to the end */
    long file_size = ftell(file_pointer);

    rewind(file_pointer);
    fclose(file_pointer);                           /* scroll through the file to the start */

    return file_size;
}

/*
 * Function to read file, supported modes (READ, READ_WRITE, READ_BIN, READ_WRITE_BIN)
 * parameter: mode, open file mode
 * parameter: file_path, path plus file name
 * return: file content on success or NULL
 */
char* read_file(int mode, char* file_path)
{
    if (mode > READ_WRITE_BIN || mode < READ)
    {
        errno = EINVAL;
        perror("The specified handling mode is not valid");
        return NULL;
    }

    long file_size = get_file_size(file_path) + 1;
    char* file_content = (char*)malloc(sizeof(char) * file_size);

    FILE* file_pointer = test_open(mode, file_path);

    if (file_pointer == NULL)
    {
        free(file_content);
        return NULL;
    }

    setbuf(stdin, NULL);
    fgets(file_content, file_size, file_pointer);       /* reading the contents of the file */
    file_content[(int)strlen(file_content)] = '\0';

    fclose(file_pointer);

    return file_content;
}

/*
 * File writing function, supported modes (WRITE, WRITE_READ, WRITE_BIN, WRITE_READ_BIN)
 * parameter: mode, open file mode
 * parameter: file_path, path plus file name
 * parameter: content, content to write into file
 */
void write_file(char* content, int mode, char* file_path)
{
    if (mode == 0)
        mode = WRITE;

    if (mode > WRITE_READ_BIN || mode < WRITE)
    {
        errno = EINVAL;
        perror("The specified handling mode is not valid");
        return;
    }

    FILE* file_pointer = test_open(mode, file_path);

    if (file_pointer == NULL)
    {
        return;
    }

    fputs(content, file_pointer);

    fclose(file_pointer);
}

/*
 * Function to edit file, supported modes (EDIT, EDIT_READ, EDIT_BIN, EDIT_READ_BIN)
 * parameter: mode, open file mode
 * parameter: file_path, path plus file name
 * parameter: content, content to append into file
 */
void edit_file(char* content, int mode, char* file_path)
{
    if (mode == 0)
        mode = EDIT;

    if (mode > EDIT_READ_BIN || mode < EDIT)
    {
        errno = EINVAL;
        perror("The specified handling mode is not valid");
        return;
    }

    FILE* file_pointer = test_open(mode, file_path);

    if (file_pointer == NULL)
    {
        return;
    }

    fputs(content, file_pointer);

    fclose(file_pointer);
}