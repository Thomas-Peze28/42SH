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
    noecho();
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
}
