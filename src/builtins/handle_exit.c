/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** handle_exit
*/

#include <stdlib.h>
#include "my.h"
#include "workspace.h"
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

int is_exit(char *str)
{
    int i = 0;
    int str_len = my_strlen(str);

    while (str[i] == ' ' || str[i] == '\t')
        i++;
    if (i + 3 >= str_len || !(str[i] == 'e' && str[i + 1] == 'x'
        && str[i + 2] == 'i' && str[i + 3] == 't'))
        return 0;
    i += 4;
    while (str[i] != '\0') {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
            i++;
        else
            return 0;
    }
    return 1;
}

static void close_ncurses(bool flag)
{
    if (flag == true)
        endwin();
}

int handle_exit(char **warray, char ***env,
    history_t *history, alias_t *aliases)
{
    for (int i = 0; warray[i] != NULL; i++) {
        if (is_exit(warray[i])) {
            free_all(0, NULL, warray);
            printv("exit\n", 2);
            free_eha(*env, history, aliases);
            close_ncurses(isatty(0) && isatty(1));
            exit(0);
        }
    }
    return 0;
}
