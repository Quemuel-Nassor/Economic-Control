/*
 * This library contains methods for handle errors
 *
 * Author: Quemuel Alves Nassor
 * Date: 23/07/21
 */

#ifndef ERROR_H
#define ERROR_H

#include <limits.h>

#if defined(__unix__) && !defined(PATH_MAX)
    #include <linux/limits.h>
#endif

#ifndef NAME_MAX
#define NAME_MAX 255
#endif

#define MAX_ERROR_MESS PATH_MAX + NAME_MAX

char * error_mess(char * msg, char * path);

#endif