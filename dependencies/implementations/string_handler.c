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
 * Function to convert long value to string
 * parameter: value, number to convert
 * return : numeric string value
 */
char* long_to_string(size_t value)
{
    int value_size = snprintf(NULL, 0, "%lu", value) + 1;
    char* string_value = (char*)malloc(sizeof(char) * value_size);

    sprintf(string_value, "%lu", value);

    string_value[value_size - 1] = '\0';

    return string_value;
}

/*
 * Function to convert double value to string
 * parameter: value, number to convert
 * return : numeric string value
 */
char* double_to_string(double value)
{
    int value_size = snprintf(NULL, 0, "%lf", value) + 1;
    char* string_value = (char*)malloc(sizeof(char) * value_size);

    sprintf(string_value, "%lf", value);

    string_value[value_size - 1] = '\0';

    return string_value;
}

/*
 * Function to split a string based on the separator parameter
 * parameter: separator, separator character
 * parameter: content, string to split
 * parameter: size, reference to return the size of the resulting string list
 * return: string list, divided by separator character
 */
char** string_split(char* separator, char* content, int* size)
{
    *size = substring_count(separator, content);
    char content_copy[strlen(content)];
    char** list_strings = (char**)malloc(sizeof(char*) * (*size));              /* allocate string list result */

    strcpy(content_copy, content);
    char* substring = strtok(content_copy, separator);                          /* move pointer to last substring */

    /* Loop to add substrings into list */
    for (*size = 0; substring != NULL;* size += 1)
    {
        list_strings[*size] = (char*)malloc( sizeof(char) * strlen(substring)); /* allocate space for the string in the new position of the list */
        strcpy(list_strings[*size], substring);                                 /* add string to list */
        substring = strtok(NULL, separator);                                    /* move pointer to last substring */
    }

    return list_strings;
}

/*
 * Function to count number of substrings
 * parameter: separator, separator character
 * parameter: content, string to split
 * return: number of substrings in a single string delimited by a separator
 */
int substring_count(char* separator, char* content)
{
    int substring_count = 0;
    char* content_copy = (char*)malloc(sizeof(char) * strlen(content));

    strcpy(content_copy, content);
    char* substring = strtok(content_copy, separator); /* move pointer to last substring */

    /* Loop to count substrings */
    for (substring_count = 0; substring != NULL; substring_count += 1)
    {
        substring = strtok(NULL, separator);
    }

    return substring_count;
}