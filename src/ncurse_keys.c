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

static void clear_and_print_prompt(int max_y)
{
    move(max_y - 1, 0);
    clrtoeol();
    printw("> ");
}

static void print_input_line(const char *input, int max_y)
{
    move(max_y - 1, 2);
    clrtoeol();
    printw("%s", input);
}

static int handle_history_up(char *input,
    int *pos, int *hist_idx, history_t *history)
{
    int max_y;
    int max_x;

    getmaxyx(stdscr, max_y, max_x);
    if (*hist_idx > 0)
        (*hist_idx)--;
    strcpy(input, history->commands[*hist_idx]);
    *pos = strlen(input);
    print_input_line(input, max_y);
    move(max_y - 1, 2 + *pos);
    return 1;
}

static int handle_history_down(char *input,
    int *pos, int *hist_idx, history_t *history)
{
    int max_x;
    int max_y;

    getmaxyx(stdscr, max_y, max_x);
    if (*hist_idx < history->count - 1) {
        (*hist_idx)++;
        strcpy(input, history->commands[*hist_idx]);
        *pos = strlen(input);
        print_input_line(input, max_y);
        move(max_y - 1, 2 + *pos);
    } else {
        input[0] = '\0';
        *pos = 0;
        print_input_line(input, max_y);
    }
    return 1;
}

static int handle_backspace(char *input, int *pos, int max_y)
{
    if (*pos > 0) {
        (*pos)--;
        input[*pos] = '\0';
        print_input_line(input, max_y);
        move(max_y - 1, 2 + *pos);
    }
    return 1;
}

int handle_input_char(int ch, char *input, int *pos, int size)
{
    if (ch >= 32 && ch < 127 && *pos < size - 1) {
        (*pos)++;
        input[(*pos)] = ch;
        input[*pos] = '\0';
        printw("%c", ch);
        return 1;
    }
    return 0;
}

int handle_enter_key(char *input, int *pos)
{
    input[*pos] = '\0';
    printw("\n");
    return 0;
}

int process_key_event(char *input,
    int *pos, int *hist_idx, history_t *history)
{
    int max[2];
    int ch = getch();

    getmaxyx(stdscr, max[0], max[1]);
    if (ch == '\n' || ch == '\r')
        return handle_enter_key(input, pos);
    if (ch == KEY_UP && history && history->count > 0)
        return handle_history_up(input, pos, hist_idx, history);
    if (ch == KEY_DOWN && history && history->count > 0)
        return handle_history_down(input, pos, hist_idx, history);
    if (ch == KEY_BACKSPACE || ch == 127 || ch == 8)
        return handle_backspace(input, pos, max[0]);
    if (handle_input_char(ch, input, pos, 1024))
        return 1;
    return 0;
}

void setup_ncurses_input(int *max_y, int *max_x, char *input)
{
    getmaxyx(stdscr, *max_y, *max_x);
    clear_and_print_prompt(*max_y);
    noecho();
    keypad(stdscr, TRUE);
    input[0] = '\0';
}

int read_input_ncurses(char *input, int size, history_t *history)
{
    int pos = 0;
    int ch = 0;
    int max_y = 0;
    int max_x = 0;
    int hist_idx = history ? history->count : 0;

    setup_ncurses_input(&max_y, &max_x, input);
    while (1) {
        if (process_key_event(input, &pos, &hist_idx, history) == 0) {
            break;
        }
        refresh();
    }
    return (pos == 0) ? -1 : 0;
}
