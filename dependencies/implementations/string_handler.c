/*
 * This library contains tools for manipulating strings
 *
 * Author: Quemuel Alves Nassor
 * Date: 30/07/21
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\string_handler.h"
#elif defined(__unix__)
#include "../include/string_handler.h"
#endif

/*
 * Function to join strings separated by specified character
 * parameter: max_length, max length of resulting string, must be greater than zero
 * parameter: separator, separator character, can be NULL
 * parameter: parameter, strings to join, the last item must be are NULL
 * return : single string with separator character between each parameter entered
 */
char* string_join(long max_length, char separator, char* parameter, ...)
{
    va_list parameters_list;
    char *string, *joined_strings = (char *)malloc(sizeof(char) * strlen(parameter));
    strcpy(joined_strings, parameter);                      /* get first parameter of argument list */

    va_start(parameters_list, parameter);                   /* set pointer to first parameter on parameter list */

    /* Iterating the parameter list */
    while ((string = va_arg(parameters_list, char*)) != NULL)
    {
        if (max_length > INDEFINITE_LENGTH && strlen(joined_strings) + strlen(string) >= max_length)
        {
            va_end(parameters_list);                        /* set pointer of parameter list to NULL */
            joined_strings[strlen(joined_strings)] = '\0';  /* set termination string character */
            return joined_strings;
        }

        /*
         *  Resize result string
         */
        size_t new_size = (strlen(joined_strings) + strlen(string));

        char* aux = (char*)realloc(joined_strings, sizeof(char) * new_size);
        if (aux != NULL)
        {
            joined_strings = aux;
        }

        if (string != NULL)
        {
            if (separator != EMPTY_SEPARATOR)
                joined_strings[strlen(joined_strings)] = separator; /* set separator character */
            strcat(joined_strings, string);
        }
    }

    va_end(parameters_list);                                        /* set pointer of parameter list to NULL */
    joined_strings[strlen(joined_strings)] = '\0';                  /* set termination string character */

    return joined_strings;
}

/*
 * Function to split a string based on the separator parameter
 * parameter: separator, separator character
 * parameter: content, string to split
 * parameter: size, reference to return the size of the resulting string list
 * return: string list, divided by separator character
 */
// char** string_split(char* separator, char* content, int* size)
// {
//     char** list_strings;// = (char**)malloc(sizeof(char*));
//     char* content_copy = (char*)malloc(sizeof(char)*strlen(content));
//     char* substring;

//     strcpy(content_copy,content);                                              /* copy string content */
//     substring = strtok(content_copy, separator);                               /* move pointer to last substring */

//     /* Loop to count substrings */
//     for (*size = 0; substring != NULL; *size+=1)
//     {
//         substring = strtok(NULL, separator);
//     }

//     list_strings = (char**)malloc(sizeof(char*)*(*size));                      /* allocate string list result */
//     substring = strtok(content, separator);                                    /* move pointer to last substring */

//     /* Loop to add substrings into list */
//     for (*size = 0; substring != NULL;* size += 1) {
//         list_strings[*size] = (char*)malloc(sizeof(char) * strlen(substring)); /* allocate space for the string in the new position of the list */
//         strcpy(list_strings[*size], substring);                                /* add string to list */
//         substring = strtok(NULL, separator);                                   /* move pointer to last substring */
//     }

//     // for (*size = 0; substring != NULL;* size += 1) {
//     //     if (size > 0)
//     //         strcat(list_strings, (char**)malloc(sizeof(char*)));               /* allocate space for new element in list */
//     //     list_strings[*size] = (char*)malloc(sizeof(char) * strlen(substring)); /* allocate space for the string in the new position of the list */
//     //     strcpy(list_strings[*size], substring);                                /* add string to list */
//     //     substring = strtok(NULL, separator);                                   /* move pointer to last substring */
//     // }

//     return list_strings;
// }