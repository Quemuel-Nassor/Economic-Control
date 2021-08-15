/*
 * This library contains tools for manipulating strings
 *
 * Author: Quemuel Alves Nassor
 * Date: 30/07/21
 */

#ifndef STRING_HANDLE_H
#define STRING_HANDLE_H

#define INDEFINITE_LENGTH 0
#define EMPTY_SEPARATOR '\0'

char* string_join(long max_length, char separator, char* parameter, ...);
// char** string_split(char* separator, char* content, int* size);

#endif