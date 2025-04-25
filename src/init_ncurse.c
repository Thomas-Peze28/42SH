/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

void init_ncurses(void)
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(1);
}
