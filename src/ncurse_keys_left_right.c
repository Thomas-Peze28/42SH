/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** 42sh
*/

#include <ncurses.h>
#include "my.h"

int handle_cursor_move(int key, int pos, int len, int max_y)
{
    if (key == KEY_LEFT && pos > 0) {
        move(max_y - 1, 2 + pos - 1);
        return pos - 1;
    }
    if (key == KEY_RIGHT && pos < len) {
        move(max_y - 1, 2 + pos + 1);
        return pos + 1;
    }
    return pos;
}

int process_left_right(int ch, int *pos, char *input)
{
    int max[2];

    getmaxyx(stdscr, max[0], max[1]);
    if (ch == KEY_LEFT || ch == KEY_RIGHT) {
        *pos = handle_cursor_move(ch, *pos, strlen(input), max[0]);
        return 1;
    }
    return 0;
}
