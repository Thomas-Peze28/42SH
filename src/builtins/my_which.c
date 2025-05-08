/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** handle_exit
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "workspace.h"
#include <stdlib.h>
#include "my.h"
#include "workspace.h"

static char *get_path_str(char **env)
{
    int i = 0;

    for (i = 0; env[i] != NULL; i++) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i] + 5;
    }
    return NULL;
}

static char **split_path(char *path_str)
{
    if (!path_str)
        return NULL;
    return my_str_to_warray(path_str, ":");
}

static char *build_filepath(char *dir, char *cmd)
{
    char *tmp = NULL;

    tmp = malloc(my_strlen(dir) + my_strlen(cmd) + 2);
    if (!tmp)
        return NULL;
    my_strcpy(tmp, dir);
    my_strcat(tmp, "/");
    my_strcat(tmp, cmd);
    return tmp;
}

static void free_path_array(char **path)
{
    int j = 0;

    if (!path)
        return;
    for (j = 0; path[j]; j++)
        free(path[j]);
    free(path);
}

static char *find_command_in_path(char *cmd, char **path)
{
    int i = 0;
    char *tmp = NULL;

    for (i = 0; path[i] != NULL; i++) {
        tmp = build_filepath(path[i], cmd);
        if (!tmp)
            continue;
        if (access(tmp, X_OK) == 0)
            return tmp;
        free(tmp);
    }
    return NULL;
}

char *find_command_path(char *cmd, char **env)
{
    char *path_str = NULL;
    char **path = NULL;
    char *result = NULL;

    if (!cmd)
        return NULL;
    if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
        return access(cmd, X_OK) == 0 ? my_strdup(cmd) : NULL;
    path_str = get_path_str(env);
    if (!path_str)
        return NULL;
    path = split_path(path_str);
    if (!path)
        return NULL;
    result = find_command_in_path(cmd, path);
    free_path_array(path);
    return result;
}

int my_which(char **warray, char **env)
{
    int i;
    char *fpath = NULL;

    if (!warray || !warray[1]) {
        printv("which: Too few arguments.\n", 2);
        return 1;
    }
    for (i = 1; warray[i] != NULL; i++) {
        fpath = find_command_path(warray[i], env);
        if (fpath) {
            printv(fpath, 1);
            printv("\n", 1);
            free(fpath);
        } else {
            printv(warray[i], 2);
            printv(": Command not found.\n", 2);
        }
    }
    return 0;
}
