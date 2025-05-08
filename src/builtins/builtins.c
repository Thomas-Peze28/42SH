/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "workspace.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ncurses.h>

static void remove_newlines(char **warray, int i)
{
    int j;

    for (j = 0; warray[i][j] != '\0'; j++) {
        if (warray[i][j] == '\n')
            warray[i][j] = '\0';
    }
}

static int handle_builtin_commands(char **warray,
    char ***env, history_t *history)
{
    if (handle_history_command(warray, history))
        return 0;
    if (my_strcmp(warray[0], "setenv") || my_strcmp(warray[0], "unsetenv"))
        return func_setenv_unsetenv(warray, env);
    if (my_strcmp(warray[0], "cd") && my_strlen(warray[0]) <= 2) {
        if (func_cd(warray, env) != 0 ||
        change_dir_env(env, getcwd(NULL, 0)) != 0)
            return 84;
        return 0;
    }
    if (my_strcmp(warray[0], "env") && my_strlen(warray[0]) <= 3)
        return func_env(warray, *env);
    if (my_strcmp(warray[0], "which"))
        return my_which(warray, *env);
    if (my_strcmp(warray[0], "clear"))
        return clear();
    if (my_strcmp(warray[0], "42sh"))
        return print_42sh_ascii();
    return -1;
}

int gest_comm(char **warray, char ***env, history_t *history)
{
    int ret;

    if (warray == NULL || warray[0] == NULL || my_strcmp(warray[0], "\n"))
        return 0;
    for (int i = 0; warray[i] != NULL; i++)
        remove_newlines(warray, i);
    ret = handle_builtin_commands(warray, env, history);
    if (ret != -1)
        return ret;
    return process_env_command(*env, warray);
}
