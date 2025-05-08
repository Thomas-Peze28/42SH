/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** handle_alias
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "workspace.h"

static char *extract_single_quoted_arg(char *arg)
{
    char *command = NULL;

    if (arg[0] == '"' && arg[strlen(arg) - 1] == '"') {
        command = my_strdup(arg + 1);
        if (!command)
            return NULL;
        command[strlen(command) - 1] = '\0';
        return command;
    }
    return NULL;
}

static int calculate_command_length(char **args, int start_idx)
{
    int total_len = 0;
    int i;

    for (i = start_idx; args[i]; i++) {
        total_len += strlen(args[i]) + 1;
    }
    return total_len;
}

static void append_first_argument(char *command, char *first_arg)
{
    if (first_arg[0] == '"')
        strcat(command, first_arg + 1);
    else
        strcat(command, first_arg);
}

static void append_remaining_args(char *command, char **args, int start_idx)
{
    int i;

    for (i = start_idx + 1; args[i]; i++) {
        strcat(command, " ");
        if (!args[i + 1] && args[i][strlen(args[i]) - 1] == '"') {
            strncat(command, args[i], strlen(args[i]) - 1);
        } else {
            strcat(command, args[i]);
        }
    }
}

static char *extract_quoted_command(char **args, int start_idx)
{
    char *command = NULL;
    int total_len;

    command = extract_single_quoted_arg(args[start_idx]);
    if (command)
        return command;
    total_len = calculate_command_length(args, start_idx);
    command = malloc(total_len + 1);
    if (!command)
        return NULL;
    command[0] = '\0';
    append_first_argument(command, args[start_idx]);
    append_remaining_args(command, args, start_idx);
    return command;
}

int handle_alias_command(char **args, alias_t *aliases)
{
    char *command = NULL;

    if (!args[1]) {
        display_aliases(aliases);
        return 0;
    }
    if (!args[2]) {
        display_single_alias(args[1], aliases);
        return 0;
    }
    command = extract_quoted_command(args, 2);
    if (!command)
        return 84;
    add_alias(aliases, args[1], command);
    free(command);
    return 0;
}
