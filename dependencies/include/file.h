/*
 * This library contains methods to manipulate files
 *
 * Author: Quemuel Alves Nassor
 * Date: 23/07/21
 */

#ifndef FILE_H
#define FILE_H

#include "error.h"

#define START_OF_FILE 0

extern const char* FILE_HANDLERS[];
extern const char DIR_SEPARATOR_CHR;

enum file_modes
{
    READ,           /* read only */
    READ_WRITE,     /* read and write (the file must exist) */
    READ_BIN,       /* read only (binary) */
    READ_WRITE_BIN, /* read and write (binary) (overwrite file if exists) */
    WRITE,          /* write only */
    WRITE_READ,     /* read and write (overwrite file if exists) */
    WRITE_BIN,      /* write only (binary) */
    WRITE_READ_BIN, /* read and write (binary) (overwrite file if exists) */
    EDIT,           /* append only */
    EDIT_READ,      /* read and append new content at end of file */
    EDIT_BIN,       /* append only (binary) */
    EDIT_READ_BIN   /* read and append new content at end of file (binary) */
};

FILE* test_open(int mode, char* file_path);
long get_file_size(char* file_path);
char* read_file(int mode, char* file_path);
void write_file(char* content, int mode, char* file_path);
void edit_file(char* content, int mode, char* file_path);

#endif