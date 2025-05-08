/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** pip_utils
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
#include "workspace.h"

void free_list_commands(char ***list_commands)
{
    int i = 0;

    for (i = 0; list_commands[i] != NULL; i++)
        my_free_warray(list_commands[i]);
    free(list_commands);
}

int verif_pip(char **warray, int nb_pipe)
{
    int i;

    for (i = 0; i <= nb_pipe; i++) {
        if (check_empty_command(warray[i]) == -1)
            return -1;
    }
    return 0;
}

char *get_path_from_env(char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        if (my_strncmp(env[i], "PATH=", 5) == 0)
            return env[i];
        i++;
    }
    return NULL;
}

static char *try_path_location(char *cmd, char *path_dir)
{
    char *filepath = NULL;

    filepath = malloc(my_strlen(path_dir) + my_strlen(cmd) + 2);
    if (!filepath)
        return NULL;
    my_strcpy(filepath, path_dir);
    my_strcat(filepath, "/");
    my_strcat(filepath, cmd);
    if (access(filepath, X_OK) == 0)
        return filepath;
    free(filepath);
    return NULL;
}

static int is_direct_path(char *cmd)
{
    if (cmd[0] == '/')
        return 1;
    if (cmd[0] == '.' && cmd[1] == '/')
        return 1;
    if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
        return 1;
    return 0;
}

static char *search_path(char **path, int start, int end, char *cmd)
{
    char *filepath = NULL;
    int i;

    for (i = start; i < end && path[i] != NULL; i++) {
        filepath = try_path_location(cmd, path[i]);
        if (filepath)
            return filepath;
    }
    return NULL;
}

static char *search_in_paths(char *cmd, char **path)
{
    char *filepath = NULL;
    int path_len = 0;

    while (path[path_len] != NULL)
        path_len++;
    filepath = search_path(path, 0, path_len, cmd);
    if (filepath) {
        free_divise_path(path);
        return filepath;
    }
    free_divise_path(path);
    return my_strdup(cmd);
}

static char *find_command_path(char *cmd, char **env)
{
    char **path = NULL;
    char *path_str = NULL;

    if (is_direct_path(cmd))
        return my_strdup(cmd);
    path_str = get_path_from_env(env);
    if (!path_str)
        return my_strdup(cmd);
    path = divise_path(path_str);
    if (!path)
        return my_strdup(cmd);
    return search_in_paths(cmd, path);
}

static char **process_command(char *cmd_str, char **env)
{
    char **cmd_args = NULL;
    char *path = NULL;

    if (cmd_str == NULL || env == NULL)
        return NULL;
    cmd_args = my_str_to_warray(cmd_str, " \n\t");
    if (cmd_args != NULL && cmd_args[0] != NULL) {
        path = find_command_path(cmd_args[0], env);
        if (path != NULL) {
            free(cmd_args[0]);
            cmd_args[0] = path;
        }
    }
    return cmd_args;
}

char ***create_list_commands(char **warray, int nb_pipe, char **env)
{
    char ***list_commands = NULL;
    int i = 0;

    list_commands = malloc(sizeof(char **) * (nb_pipe + 2));
    if (!list_commands)
        return NULL;
    for (i = 0; i < nb_pipe + 1; i++)
        list_commands[i] = process_command(warray[i], env);
    list_commands[nb_pipe + 1] = NULL;
    return list_commands;
}
