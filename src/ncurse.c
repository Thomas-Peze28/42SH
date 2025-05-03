/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static int read_input_ncurses(char *input, int size)
{
    int result = 0;

    printw("> ");
    refresh();
    echo();
    result = getnstr(input, size - 1);
    noecho();
    if (result == ERR) {
        input[0] = '\0';
        return -1;
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
