/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** Gestion des pipes
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include "my.h"
#include "workspace.h"

static int count_nb_pipe(char *warray)
{
    int i = 0;
    int nb_pipe = 0;

    if (warray == NULL)
        return 0;
    while (warray[i] != '\0') {
        if (warray[i] == '|')
            nb_pipe++;
        i++;
    }
    if (nb_pipe > 10)
        return 0;
    return nb_pipe;
}

static int execute_multiple_pipes(char ***commands, int cmd_count, char **env)
{
    pipe_data_t data;

    if (cmd_count <= 0)
        return -1;
    if (cmd_count == 1)
        return execute_single_command(commands[0], env);
    data.cmd_count = cmd_count;
    if (setup_pipes(&data) == -1)
        return -1;
    return run_commands(commands, &data, env);
}

static int is_pipe_at_start_or_end(int position, int is_pipe, char *warray)
{
    if (is_pipe && (position == 0 || warray[position + 1] == '\0'))
        return 1;
    return 0;
}

static int is_adjacent_to_pipe(int position, int is_pipe, char *warray)
{
    if (is_pipe && (position > 0 && warray[position - 1] == '|'))
        return 1;
    if (is_pipe && warray[position + 1] == '|')
        return 1;
    return 0;
}

static int check_invalid_pipes(char *warray)
{
    int i = 0;
    int is_pipe = 0;

    while (warray[i]) {
        is_pipe = (warray[i] == '|');
        if (is_pipe_at_start_or_end(i, is_pipe, warray)) {
            printv("Invalid null command.\n", 2);
            return 1;
        }
        if (is_adjacent_to_pipe(i, is_pipe, warray)) {
            printv("Invalid null command.\n", 2);
            return 1;
        }
        i++;
    }
    return 0;
}

static int handle_pipe_error(char **warray)
{
    if (warray)
        my_free_warray(warray);
    printv("Invalid null command.\n", 2);
    return 0;
}

static int cleanup_and_return(int result, char **warray, char ***list_commands)
{
    my_free_warray(warray);
    free_list_commands(list_commands);
    return result;
}

static int init_pipe_execution(char *warray, char ***env,
    int *nb_pipe, char ***n_warray)
{
    if (warray == NULL || env == NULL)
        return -1;
    if (check_invalid_pipes(warray))
        return 0;
    *nb_pipe = count_nb_pipe(warray);
    if (*nb_pipe == 0)
        return -1;
    *n_warray = my_str_to_warray(warray, "|");
    if (*n_warray == NULL || verif_pip(*n_warray, *nb_pipe) == -1)
        return handle_pipe_error(*n_warray);
    return 1;
}

int execute_piped_commands(char *warray, char ***env)
{
    int nb_pipe = 0;
    int result = 0;
    char **n_warray = NULL;
    char ***list_commands = NULL;
    int status;

    status = init_pipe_execution(warray, env, &nb_pipe, &n_warray);
    if (status <= 0)
        return status;
    list_commands = create_list_commands(n_warray, nb_pipe, *env);
    if (list_commands == NULL) {
        my_free_warray(n_warray);
        return 0;
    }
    result = execute_multiple_pipes(list_commands, nb_pipe + 1, *env);
    return cleanup_and_return(result, n_warray, list_commands);
}
