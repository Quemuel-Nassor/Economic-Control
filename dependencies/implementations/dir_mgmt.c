/*
 * Library to create folders, get the current directory path, and complement the file names with the
 * current directory path and delete files and directory trees
 *
 * Author: Quemuel Alves Nassor
 * Date: 27/12/20
 */

#include <stdarg.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#if defined(_WIN32) || defined(WIN32)
    #include "..\include\dir_mgmt.h"
    const char DIR_SEPARATOR_CHR = '\\';
#elif defined(__unix__)
    #include "../include/dir_mgmt.h"
    const char DIR_SEPARATOR_CHR = '/';
#endif

/*
    Function to check if directory exist
        parameter: path, path to check
        return: errno code on error or EXIT_SUCCESS on success;
*/
int check_if_dir_exist(char *path)
{
    struct stat st = {0};         /*File structure*/
    int result = stat(path, &st); /*Testing if path is valid*/
    char *errorMsg = error_mess("The directory",path);
    // strcpy(errorMsg, error_mess("The directory",path));
    result != EXIT_SUCCESS ? strcat(errorMsg, " does not exist") : strcat(errorMsg, " exists");
    perror(errorMsg);
    return result;
}

/*
    Function to create a single folder
        parameter: path, place where the folder will be created
        return: errno code on error or EXIT_SUCCESS on success;
*/
#if defined(_WIN32) || defined(WIN32)
    #include <direct.h>
    int mk_dir(char *path)
    {

        if (mkdir(path) != 0)
        {
            char *errorMessage = error_mess("Failed to create folder", path);
            perror(errorMessage);
        }

        return errno;
    }
#elif __unix__
    #include <unistd.h>
    int mk_dir(char *path)
    {

        if (mkdir(path, 0777) != 0)
        {
            char *errorMessage = error_mess("Failed to create folder", path);
            perror(errorMessage);
        }

        return errno;
    }

#endif

/*
    Function to get the parent directory of a path
        parameter: path, path from where will get parent
        parameter: parent_path, path parent directory
        return: errno code on error or EXIT_SUCCESS on success;
*/
int get_parent_dir(char *path, char *parent_path)
{
    
    struct stat st = {0};                                         /*File structure*/
    char *last_file_or_folder = strrchr(path, DIR_SEPARATOR_CHR); /*Find and retrieve the string starting with the last character DIR_SEPARATOR_CHR*/
    size_t size_parent = (last_file_or_folder != NULL ? strlen(last_file_or_folder) : 0);
    size_t size = (strlen(path) - size_parent);

    parent_path = (char *)malloc(size * sizeof(char));
    parent_path[0] = '\0';

    if (last_file_or_folder != NULL)
    {
        strncpy(parent_path, path, size); /*Copy path without the last folder*/
        parent_path[size] = '\0';
    }


    return stat(path, &st); /*Testing if path is valid*/
}


/*
    Function to create directory tree
        parameter: path, place where the folder(s) will be created
        return: errno code on error or EXIT_SUCCESS on success;
*/
int mk_dir_tree(char *path)
{

    /* struct stat st = {0};                               /*File structure*/
    /* char *sep = strrchr(path, DIR_SEPARATOR_CHR);       /*Find and retrieve the string from the last character DIR_SEPARATOR_CHR*/
    /* char new_path[strlen(path)];                   /*New path without the last folder*/
    /* new_path[0] = '\0';*/
    /* if(sep != NULL){*/
    /*     strncpy(new_path,path,(sep-path));              /*Copy path without the last folder*/
    /*     new_path[(sep-path)] = '\0';*/
    /* }*/

    /* int result = stat(path, &st);                       /*Testing if path is valid*/

    char *parent_path;
    int result = get_parent_dir(path, parent_path);
    printf("\n\npath {%s} - parent {%s}",path,parent_path);

    if (result == EXIT_SUCCESS && errno == EXIT_SUCCESS)
    {
        errno = EEXIST;
        char *errorMessage = error_mess("Directory tree exist", path);
        perror(errorMessage);
    }

    if (result != EXIT_SUCCESS && errno == ENOENT)
    {
        if(strlen(parent_path) != 0) mk_dir_tree(parent_path); /*Recursion call*/
        mk_dir(path);             /*Return of recursion*/
        /* result = stat(path, &st);                       /*Testing if path is valid*/
        get_parent_dir(path, parent_path) == 0 ? errno = EXIT_SUCCESS : 0;
    }
    else if ((result != EXIT_SUCCESS && errno != ENOENT) || (result != EXIT_SUCCESS && errno == ENOENT && strlen(parent_path) == 0))
    {
        char *errorMessage = error_mess("Failed to create directory tree", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to remove directory tree
        parameter: path, place where the folder (s) are
        return: errno code on error or EXIT_SUCCESS on success;
*/
int rm_dir_tree(char *path)
{

    /* struct stat st = {0};                               /*File structure*/
    /* char new_path[strlen(path)];                        /*New path without the last folder*/
    /* char *sep = strrchr(path, DIR_SEPARATOR_CHR);       /*Find and retrieve the string from the last character DIR_SEPARATOR_CHR*/
    /* new_path[0] = '\0';*/
    /* if(sep != NULL){*/
    /*     strncpy(new_path,path,(sep-path));              /*Copy path without the last folder*/
    /*     new_path[(sep-path)] = '\0';*/
    /* }*/

    rmdir(path);

    char *parent_path;
    int result = get_parent_dir(path, parent_path);

    /* int result = stat(path, &st);                       /*Testing if path is valid*/

    if (strlen(parent_path) != 0 && errno == ENOENT)
    {
        rm_dir_tree(parent_path);
        /* result = stat(path, &st);                       /*Testing if path is valid*/
        get_parent_dir(path, parent_path) == EXIT_FAILURE ? errno = EXIT_SUCCESS : 0;
    }
    else if (strlen(parent_path) == 0 && errno != ENOENT)
    {
        char *errorMessage = error_mess("Failed to remove directory tree", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to get current directory path
        parameter: void
        return: NULL on error or current directory path on success;
*/
char *get_cur_dir(void)
{
    size_t size = PATH_MAX * sizeof(char);
    char *BASE_PATH = (char *)malloc(size);

    if (___getcwd(BASE_PATH, size) == NULL)
    {
        BASE_PATH = NULL;
        perror("Failed to get the current working directory");
    }

    return BASE_PATH;
}

/*
    Function to join directory path with file name or folder name
        parameters: params, file or folder names that will be joined
        return: joined path
*/
int join_path(char *path, char *params,...)
{
    va_list words;
    char *folder_or_filename;
    int params_count = 0;

    if(strcmp(path,"\0")==0) 
    {
        strcpy(path,params); 
    }
    else
    {
        path[strlen(path)] = DIR_SEPARATOR_CHR;
        strcat(path,params); 
    }

    /* Initializing parameter list */
    va_start(words, params);

    /* Iterating the parameter list */
    while ((folder_or_filename = va_arg(words, char*))!= NULL)  
    {
        if(strlen(path) == PATH_MAX) break;

        size_t param_size = strlen(folder_or_filename);

        if(params_count >= 0 && folder_or_filename != NULL) path[strlen(path)] = DIR_SEPARATOR_CHR;
        strcat(path, folder_or_filename);

        if (params_count == 0 && (folder_or_filename == NULL || param_size == 0))
        {
            char *errorMessage = error_mess("Failed to join paths (",path);
            strcat(errorMessage, " and\0");
            strcat(errorMessage, folder_or_filename);
            perror(errorMessage);
        }

        params_count++;
    }

    /* Ending parameter list */
    va_end(words);

    return errno;
}

/*
    Function to list content of an folder
        parameter: path, location of the content that will be listed
        return: list of strings with content of the informed path
*/
char *list_dir(char *path)
{
    char *listContent = (char *)malloc((NAME_MAX + 1) * sizeof(char));
    char *errorMessage = "\0";
    listContent[0] = '\0';

    DIR *directory = opendir(path);
    struct dirent *lsdir;

    if (errno == 0)
    {

        /*Loop to search and concatenate content*/
        while ((lsdir = readdir(directory)) != NULL)
        {
            if (strcmp(lsdir->d_name, ".") != 0 && strcmp(lsdir->d_name, "..") != 0)
            {
                char *aux = listContent;
                listContent = (char *)malloc(sizeof(lsdir->d_name) + sizeof(aux));
                strcpy(listContent, aux);
                strcat(listContent, lsdir->d_name);
                listContent[strlen(listContent)] = ',';
            }
        };

        listContent[strlen(listContent) - 1] = '\0';
    }

    if (errno == ENOENT || errno != 0)
    {
        listContent = NULL;
        errorMessage = error_mess("Failed to list content of informed path", path);
        perror(errorMessage);
    }
    else if (strlen(listContent) == 0 && errno == 0)
    {
        listContent = NULL;
        errno = ENODATA;
        errorMessage = error_mess("Directory is empty", path);
        perror(errorMessage);
    }

    return listContent;
}

/*
    Function to remove multiple files from one place
        parameter: path, place of the content to be removed
        return: errno code in error or EXIT_SUCCESS in success;
*/
int rm_files(char *path)
{

    char *listContent = list_dir(path); /*Informed directory contents*/
    int i = 0;
    size_t size = strlen(listContent);
    char name[NAME_MAX + 1] = "\0";

    if (errno == 0)
    {
        /*Loop to identify and remove files*/
        for (i = 0; i <= size; i++)
        {

            if (listContent[i] != ',' && listContent[i] != '\0')
            {
                name[strlen(name)] = listContent[i];
            }
            else
            {
                char *extension = strrchr(name, '.'); /*Find and retrieve the string starting with the last character '.'*/
                char fullpath[PATH_MAX] = "\0";
                join_path(fullpath, path);
                join_path(fullpath, name);

                if (extension != NULL)
                {
                    remove(fullpath);

                    if (errno != 0 || (strcmp(fullpath, path) == 0 || strlen(name) == 0))
                    {
                        i = size + 1;
                        char *errorMessage = error_mess("Failed to clean item", fullpath);
                        perror(errorMessage);
                    }
                }

                int j;
                for (j = 0; j < PATH_MAX + 1; j++)
                {
                    fullpath[j] = '\0';
                    j < (NAME_MAX + 1) ? name[j] = '\0' : 0;
                }
            }
        }
    }

    if (strlen(path) == 0 || errno != 0)
    {
        char *errorMessage = error_mess("Failed to clean items of informed path", path);
        perror(errorMessage);
    }

    return errno;
}

/*
    Function to remove multiple contents into directory
        parameter: path, place of the content to be removed
        return: errno code in error or EXIT_SUCCESS in success;
*/
int rm_all(char *path)
{

    printf("\ninicio da função\n");

    /* printf("\ncaminho {%s}", path);*/

    /* printf("\nconteudo do diretorio {%s}", LIST_DIR(path));*/

    /* struct stat st = {0};                               /*File structure*/
    char *listContent = list_dir(path), *parent; /*Informed directory contents*/
    int i = 0;
    size_t size = 0;
    char name[NAME_MAX + 1] = "\0";
    size = listContent != NULL ? strlen(listContent) : 0;

    /* printf("\nconteudo do diretorio {%s}", listContent);*/
    /* printf("\nsize {%i}", size);*/

    int result = get_parent_dir(path, parent);
    printf("result {%i}", result);

    if (result == 0 && size > 0)
    {
        rm_files(path); /*cleaning files from current dir*/
        /* listContent = LIST_DIR(path);*/
        printf("\nremovendo arquivos do diretorio {%s}", path);
        setbuf(stdin, NULL);
        getchar();
    }

    printf("\nremoveu os arquivos");

    if ((errno == 0 || errno == ENODATA) && size > 0)
    {
        /*Loop to identify and remove files*/
        for (i = 0; i <= size; i++)
        {

            if (listContent[i] != ',' && listContent[i] != '\0')
            {
                name[strlen(name)] = listContent[i];
            }
            else
            {

                char *extension = strrchr(name, '.'); /*Find and retrieve the string starting with the last character '.'*/
                char fullpath[PATH_MAX] = "\0";
                int j;

                join_path(fullpath, path);
                join_path(fullpath, name);

                if (extension == NULL)
                {

                    if (errno == 0 || errno == ENODATA)
                    {
                        printf("\n\n recursive to {%s}\n\n", fullpath);
                        setbuf(stdin, NULL);
                        getchar();
                        rm_all(fullpath); /*Recursive call*/
                        printf("removendo arvore de diretorio {%s}", name);
                        rm_dir_tree(name); /* Removing dir tree*/
                    }
                    printf("\n\n recursive out {%s}\n\n", path);
                    setbuf(stdin, NULL);
                    getchar();
                    /**/
                    /* remove(fullpath);*/

                    if (errno != 0 || (strcmp(fullpath, path) == 0 || strlen(name) == 0))
                    {
                        i = size + 1;
                        char *errorMessage = error_mess("Failed to clean item", fullpath);
                        perror(errorMessage);
                    }
                }

                for (j = 0; j < PATH_MAX + 1; j++)
                {
                    fullpath[j] = '\0';
                    j < (NAME_MAX + 1) ? name[j] = '\0' : 0;
                }
            }
        }
    }

    if (strlen(path) == 0 || errno != 0)
    {
        printf("errno {%i}", errno);
        char *errorMessage = error_mess("Failed to clean items of informed path", path);
        perror(errorMessage);
    }
    else if (errno == ENOTEMPTY)
    {
        char *errorMessage = error_mess("Found and directory that not can be deleted (", path);
        perror(errorMessage);
    }

    return errno;
}
