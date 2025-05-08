/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** manage_history
*/

#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include "my.h"
#include "workspace.h"

history_t *init_history(int capacity)
{
    history_t *history = malloc(sizeof(history_t));

    if (!history)
        return NULL;
    history->commands = malloc(sizeof(char *) * capacity);
    if (!history->commands) {
        free(history);
        return NULL;
    }
    for (int i = 0; i < capacity; i++)
        history->commands[i] = NULL;
    history->count = 0;
    history->capacity = capacity;
    return history;
}

static char *prepare_command_for_history(history_t *history, char *command)
{
    char *trimmed_command = NULL;
    int i = 0;

    if (!history || !command || command[0] == '\0')
        return NULL;
    while (command[i] && (command[i] == ' ' ||
        command[i] == '\t' || command[i] == '\n'))
        i++;
    if (command[i] == '\0')
        return NULL;
    if (history->count > 0 &&
        my_strcmp(history->commands[history->count - 1], &command[i]))
        return NULL;
    trimmed_command = my_strdup(&command[i]);
    return trimmed_command;
}

void add_to_history(history_t *history, char *command)
{
    char *trimmed_command = prepare_command_for_history(history, command);
    int i;

    if (!trimmed_command)
        return;
    if (history->count == history->capacity) {
        free(history->commands[0]);
        for (i = 0; i < history->capacity - 1; i++)
            history->commands[i] = history->commands[i + 1];
        history->count--;
    }
    history->commands[history->count] = trimmed_command;
    history->count++;
}

static void print_history_line(int i, int count, char *command)
{
    for (int j = my_nbrlen(i + 1); j < my_nbrlen(count); j++)
        my_putchar(' ');
    printf("%d   %s", i + 1, command);
}

static void print_history_line_tty(int i, int count, char *command)
{
    for (int j = my_nbrlen(i + 1); j < my_nbrlen(count); j++)
        printw(" ");
    printw("%d   %s\n", i + 1, command);
    refresh();
}

void display_history(history_t *history)
{
    int i;

    if (!history)
        return;
    for (i = 0; i < history->count; i++) {
        if (isatty(0) && isatty(1))
            print_history_line_tty(i, history->count, history->commands[i]);
        else
            print_history_line(i, history->count, history->commands[i]);
    }
}

static void free_history_command(history_t *history)
{
    int i;

    for (i = 0; i < history->count; i++) {
        if (history->commands[i])
            free(history->commands[i]);
    }
}

void free_history(history_t *history)
{
    if (!history)
        return;
    if (history->commands) {
        free_history_command(history);
        free(history->commands);
    }
    free(history);
}

int handle_history_command(char **warray, history_t *history)
{
    if (!warray || !history)
        return 84;
    if (my_strcmp(warray[0], "history") || my_strcmp(warray[0], "!")) {
        display_history(history);
        return 1;
    }
    return 0;
}
