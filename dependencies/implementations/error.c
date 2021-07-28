/*
 * This library contains methods for handle errors
 *
 * Author: Quemuel Alves Nassor
 * Date: 23/07/21
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#if defined(_WIN32) || defined(WIN32)
#include "..\include\error.h"
#elif defined(__unix__)
#include "../include/error.h"
#endif

/*
 * Function to validate error message
 * parameter: msg, error message to return
 * parameter: param, place of error or parameter to message
 * return: validated error message on success or empty on failure
 */
char* error_mess(char* msg, char* param)
{
    int sizeMsg = (int)strlen(msg);
    int sizeParam = (int)strlen(param);
    char* errorMessage = (char*)malloc(MAX_ERROR_MESS * sizeof(char));

    if ((msg == NULL || sizeMsg == 0) && (param == NULL || sizeParam == 0))
    {
        free(errorMessage);
        errno = EINVAL;
        perror("Invalid message");
    }
    else if ((sizeMsg + sizeParam) > MAX_ERROR_MESS)
    {
        free(errorMessage);
        errno = EMSGSIZE;
        perror("The error message is too long");
    }
    else
    {
        if (msg != NULL && sizeMsg > 0)
        {
            strcpy(errorMessage, msg);
        }
        else
        {
            strcpy(errorMessage, "\0");
        }

        if (param != NULL && sizeParam > 0)
        {
            strcat(errorMessage, " (");
            strcat(errorMessage, param);
            strcat(errorMessage, ")\0");
        }
    }

    return errorMessage;
}