/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** child_exec_process
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my.h"
#include "workspace.h"
#include <stddef.h>
#include <ncurses.h>

static void handle_stdin_redirect(int in_fd)
{
    if (in_fd != STDIN_FILENO) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
}

static void handle_stdout_redirect(int out_fd)
{
    if (out_fd != STDOUT_FILENO) {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

static void close_unused_fds(int in_fd, int out_fd)
{
    if (in_fd != STDIN_FILENO && in_fd != out_fd)
        close(in_fd);
    if (out_fd != STDOUT_FILENO && in_fd != out_fd)
        close(out_fd);
}

static void handle_command_errors(char **args)
{
    if (args == NULL || args[0] == NULL) {
        printv("Invalid null command.\n", 2);
        exit(1);
    }
    if (access(args[0], F_OK) != 0) {
        printv(args[0], 2);
        printv(": Command not found.\n", 2);
        exit(1);
    }
    if (access(args[0], X_OK) != 0) {
        printv(args[0], 2);
        printv(": Permission denied.\n", 2);
        exit(1);
    }
}

static void child_exec_process(char **args, int in_fd, int out_fd, char **env)
{
    char *buffer;

    handle_stdin_redirect(in_fd);
    handle_stdout_redirect(out_fd);
    close_unused_fds(in_fd, out_fd);
    handle_command_errors(args);
    buffer = execve_and_get_stdout(args[0], args, env);
    if (buffer != NULL)
        printv(buffer, 1);
    printv(args[0], 2);
    printv(": Command not found.\n", 2);
    exit(1);
}

pid_t fork_and_execute(char **args, int in_fd, int out_fd, char **env)
{
    pid_t pid = fork();

    if (pid < 0)
        return -1;
    if (pid == 0)
        child_exec_process(args, in_fd, out_fd, env);
    return pid;
}
