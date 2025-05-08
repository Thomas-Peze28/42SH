/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** run_commands_pipe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include "my.h"
#include "workspace.h"

int setup_pipes(pipe_data_t *data)
{
    int i = 0;

    if (data->cmd_count <= 1 || data->cmd_count > 11)
        return -1;
    for (i = 0; i < data->cmd_count - 1; i++) {
        if (pipe(data->pipes[i]) == -1)
            return -1;
    }
    return 0;
}

static void get_io_fds(pipe_data_t *data, int i, int *in_fd, int *out_fd)
{
    *in_fd = STDIN_FILENO;
    *out_fd = STDOUT_FILENO;
    if (i > 0)
        *in_fd = data->pipes[i - 1][0];
    if (i < data->cmd_count - 1)
        *out_fd = data->pipes[i][1];
}

int execute_single_command(char **cmd, char **env)
{
    pid_t pid = fork_and_execute(cmd, STDIN_FILENO, STDOUT_FILENO, env);

    waitpid(pid, NULL, 0);
    return 0;
}

static void init_pipes_for_commands(pipe_data_t *data)
{
    int i;

    for (i = 0; i < data->cmd_count - 1; i++) {
        if (pipe(data->pipes[i]) == -1)
            return;
    }
}

static void handle_null_command(pipe_data_t *data, int i)
{
    if (i > 0)
        close(data->pipes[i - 1][0]);
    if (i < data->cmd_count - 1)
        close(data->pipes[i][1]);
}

static void close_pipe_after_fork(pipe_data_t *data, int i)
{
    if (i > 0)
        close(data->pipes[i - 1][0]);
    if (i < data->cmd_count - 1)
        close(data->pipes[i][1]);
}

static int get_process_exit_status(pid_t pid)
{
    int status = 0;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return 0;
}

static int wait_for_child_processes(pipe_data_t *data)
{
    int i;
    int last_status = 0;

    for (i = 0; i < data->cmd_count; i++) {
        if (data->pids[i] > 0)
            last_status = get_process_exit_status(data->pids[i]);
    }
    return last_status;
}

int execute_each_command(char ***commands, pipe_data_t *data, char **env)
{
    int i;
    int in_fd = 0;
    int out_fd = 0;

    for (i = 0; i < data->cmd_count; i++) {
        get_io_fds(data, i, &in_fd, &out_fd);
        if (commands[i] == NULL || commands[i][0] == NULL) {
            handle_null_command(data, i);
            continue;
        }
        data->pids[i] = fork_and_execute(commands[i], in_fd, out_fd, env);
        close_pipe_after_fork(data, i);
    }
    return wait_for_child_processes(data);
}

int run_commands(char ***commands, pipe_data_t *data, char **env)
{
    init_pipes_for_commands(data);
    return execute_each_command(commands, data, env);
}
