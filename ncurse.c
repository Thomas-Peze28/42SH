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

static int create_pipe_and_fork(int pipefd[2], pid_t *pid)
{
    int ret;

    ret = pipe(pipefd);
    if (ret == -1)
        return -1;
    *pid = fork();
    if (*pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return -1;
    }
    return 0;
}

static void exec_child_process(int pipefd[2],
    char *path, char **argv, char **envp)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    dup2(pipefd[1], STDERR_FILENO);
    close(pipefd[1]);
    execve(path, argv, envp);
    exit(127);
}

static char *read_from_pipe(int fd)
{
    char buffer[4096];
    char *output = NULL;
    size_t size = 0;
    ssize_t len;
    char *tmp;

    len = read(fd, buffer, sizeof(buffer));
    while (len > 0) {
        tmp = realloc(output, size + len + 1);
        if (!tmp) {
            free(output);
            return NULL;
        }
        output = tmp;
        memcpy(output + size, buffer, len);
        size += len;
        output[size] = '\0';
        len = read(fd, buffer, sizeof(buffer));
    }
    return output;
}

char *execve_and_get_stdout(char *path, char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;
    char *output = NULL;

    if (create_pipe_and_fork(pipefd, &pid) == -1)
        return NULL;
    if (pid == 0)
        exec_child_process(pipefd, path, argv, envp);
    close(pipefd[1]);
    output = read_from_pipe(pipefd[0]);
    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    return output;
}

void printv(char *text, int status)
{
    if (!isatty(0) || !isatty(1))
        write(status, text, strlen(text));
    else {
        printw("%s", text);
        refresh();
    }
}

static int read_input_ncurses(char *input, int size)
{
    int result = 0;
    int max_y;
    int max_x;

    getmaxyx(stdscr, max_y, max_x);
    move(max_y - 1, 0);
    clrtoeol();
    printv("> ", 1);
    echo();
    result = getnstr(input, size - 1);
    noecho();
    if (result == ERR) {
        input[0] = '\0';
        return -1;
    }
    if (input[0] == '\0') {
        refresh();
    }
    return 0;
}

int get_line_ncurses(char **buffer)
{
    const int NCURSES_MAX_INPUT = 1024;
    char input[NCURSES_MAX_INPUT];
    int len;

    refresh();
    if (*buffer != NULL) {
        free(*buffer);
        *buffer = NULL;
    }
    if (read_input_ncurses(input, NCURSES_MAX_INPUT) == -1) {
        len = 0;
    } else {
        len = strlen(input);
    }
    *buffer = malloc(len + 1);
    if (*buffer == NULL)
        return -1;
    strcpy(*buffer, input);
    return len;
}
