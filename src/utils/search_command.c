/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** search_command
*/

#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "my.h"
#include "workspace.h"
#include "ncurses.h"

static char *build_filepath(char *dir, char *cmd)
{
    int len;
    char *filepath;

    if (cmd[0] == '/' || cmd[0] == '.' || dir[0] == '\0') {
        len = my_strlen(cmd) + 1;
        filepath = malloc(sizeof(char) * len);
        if (!filepath)
            return NULL;
        my_strcpy(filepath, cmd);
        return filepath;
    }
    len = my_strlen(dir) + my_strlen(cmd) + 2;
    filepath = malloc(sizeof(char) * len);
    if (!filepath)
        return NULL;
    my_strcpy(filepath, dir);
    my_strcat(filepath, "/");
    my_strcat(filepath, cmd);
    return filepath;
}

int check_status_code(int status)
{
    if (status == 0)
        return 0;
    if (status == 139)
        printv("Segmentation fault (core dumped)\n", 2);
    if (status == 136)
        printv("Floating exception (core dumped)\n", 2);
    if (status == 11)
        printv("Segmentation fault\n", 2);
    if (status == 8)
        printv("Floating exception\n", 2);
    if (status == 132)
        printv("Quit (core dumped)\n", 2);
    if (status == 131)
        printv("Quit\n", 2);
    return 0;
}

static int fork_and_execute_comm(char *filepath, char **command, char **env)
{
    pid_t pid;
    int status;
    char *buffer;

    pid = fork();
    if (pid == 0) {
        buffer = execve_and_get_stdout(filepath, command, env);
        if (buffer)
            printv(buffer, 1);
        exit(84);
    }
    waitpid(pid, &status, 0);
    check_status_code(status);
    return status;
}

int exec_with_redirection(char *dir, char **command,
    char **env, redirection_t *redir)
{
    char *filepath = build_filepath(dir, command[0]);
    int status;
    int redirect_status = 0;

    if (!filepath || access(filepath, X_OK) != 0) {
        free(filepath);
        return -1;
    }
    if (redir && redir->type > 0)
        redirect_status = setup_redirection(redir);
    if (redirect_status < 0) {
        free(filepath);
        return 0;
    }
    status = fork_and_execute_comm(filepath, command, env);
    if (redir && redir->type > 0)
        cleanup_redirection(redir);
    free(filepath);
    return status;
}

int try_exec_command(char *dir, char **command, char **env)
{
    return exec_with_redirection(dir, command, env, NULL);
}

static int try_direct_execution(char **command,
    char **env, redirection_t *redir)
{
    int ret;

    if (command[0][0] != '/' && command[0][0] != '.')
        return -1;
    ret = exec_with_redirection("", command, env, redir);
    if (ret != -1)
        return ret;
    return -1;
}

static int search_in_path(char **path, char **command,
    char **env, redirection_t *redir)
{
    int i = 0;
    int ret;

    for (; path[i] != NULL; i++) {
        ret = exec_with_redirection(path[i], command, env, redir);
        if (ret != -1)
            return ret;
    }
    return -1;
}

int search_command(char **path, char **command, char **env)
{
    int ret;
    redirection_t redir = {0, NULL, 0};

    if (!path || !command || !env)
        return 84;
    handle_redirections(command, &redir);
    ret = try_direct_execution(command, env, &redir);
    if (ret != -1) {
        cleanup_redirection(&redir);
        return ret;
    }
    ret = search_in_path(path, command, env, &redir);
    if (ret != -1) {
        cleanup_redirection(&redir);
        return ret;
    }
    cleanup_redirection(&redir);
    printv(command[0], 2);
    printv(": Command not found.\n", 2);
    return 0;
}
