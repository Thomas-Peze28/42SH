/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** redirection handling
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "my.h"
#include "workspace.h"

static int is_redirection(char *str)
{
    if (str == NULL)
        return 0;
    if (my_strcmp(str, ">>"))
        return 2;
    if (my_strcmp(str, ">"))
        return 1;
    return 0;
}

static void remove_redirection_from_array(char **warray, int start_idx)
{
    int i = start_idx;

    while (warray[i + 2] != NULL) {
        free(warray[i]);
        warray[i] = my_strdup(warray[i + 2]);
        i++;
    }
    free(warray[i]);
    warray[i] = NULL;
    free(warray[i + 1]);
}

int handle_redirections(char **warray, redirection_t *redir)
{
    int i = 0;
    int red_type = 0;

    if (warray == NULL || redir == NULL)
        return -1;
    redir->type = 0;
    redir->file = NULL;
    while (warray[i] != NULL) {
        red_type = is_redirection(warray[i]);
        if (red_type > 0 && warray[i + 1] != NULL) {
            redir->type = red_type;
            redir->file = my_strdup(warray[i + 1]);
            remove_redirection_from_array(warray, i);
            return 0;
        }
        i++;
    }
    return 0;
}

static int open_output_file(redirection_t *redir)
{
    int fd;
    int flags = O_WRONLY | O_CREAT;

    if (redir->type == 1)
        flags |= O_TRUNC;
    else if (redir->type == 2)
        flags |= O_APPEND;
    else
        return -1;
    fd = open(redir->file, flags, 0644);
    if (fd == -1) {
        printv(redir->file, 2);
        printv(": Permission denied.\n", 2);
    }
    return fd;
}

int setup_redirection(redirection_t *redir)
{
    int fd;

    if (redir->type == 0)
        return 0;
    redir->original_fd = dup(STDOUT_FILENO);
    if (redir->original_fd == -1)
        return -1;
    fd = open_output_file(redir);
    if (fd == -1)
        return -1;
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

void cleanup_redirection(redirection_t *redir)
{
    if (redir->type > 0) {
        dup2(redir->original_fd, STDOUT_FILENO);
        close(redir->original_fd);
        free(redir->file);
        redir->file = NULL;
    }
    redir->type = 0;
}
