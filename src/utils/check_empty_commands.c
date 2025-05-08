/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** check_emptycommands
*/

#include "my.h"
#include "workspace.h"
#include <stdlib.h>

int is_non_whitespace(char c)
{
    return c != ' ' && c != '\t' && c != '\n';
}

int check_empty_command(char *command)
{
    int j = 0;

    if (command == NULL)
        return -1;
    while (command[j] != '\0') {
        if (is_non_whitespace(command[j]))
            return 0;
        j++;
    }
    return -1;
}
