/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** alias_commands
*/

#include <stdlib.h>
#include "my.h"
#include "workspace.h"

static void extract_name_command(char *arg, char **name, char **command)
{
    int i = 0;

    *name = NULL;
    *command = NULL;
    while (arg[i] != '\0' && arg[i] != '=')
        i++;
    if (arg[i] == '=') {
        arg[i] = '\0';
        *name = arg;
        *command = &arg[i + 1];
    }
}

static int create_alias_from_args(char **warray, alias_t *aliases)
{
    char *name = warray[1];
    char *command = NULL;
    int cmd_len = 0;
    int i;

    for (i = 2; warray[i]; i++)
        cmd_len += my_strlen(warray[i]) + 1;
    command = malloc(cmd_len);
    if (!command)
        return 84;
    command[0] = '\0';
    for (i = 2; warray[i]; i++) {
        if (i > 2)
            my_strcat(command, " ");
        my_strcat(command, warray[i]);
    }
    add_alias(aliases, name, command);
    free(command);
    return 0;
}

static int process_name_command_arg(char *arg, alias_t *aliases)
{
    char *name = NULL;
    char *command = NULL;

    extract_name_command(arg, &name, &command);
    if (name && command) {
        add_alias(aliases, name, command);
        name[my_strlen(name)] = '=';
        return 0;
    }
    return -1;
}

static void display_single_alias(char *alias_name, alias_t *aliases)
{
    char *command = get_alias_command(aliases, alias_name);

    if (command) {
        printv("alias ", 1);
        printv(alias_name, 1);
        printv("='", 1);
        printv(command, 1);
        printv("'\n", 1);
    } else {
        printv("alias: ", 2);
        printv(alias_name, 2);
        printv(" not found\n", 2);
    }
}

int handle_alias_command(char **warray, alias_t *aliases)
{
    if (!warray || !aliases)
        return 84;
    if (warray[1] == NULL) {
        display_aliases(aliases);
        return 0;
    }
    if (warray[1] && warray[2])
        return create_alias_from_args(warray, aliases);
    if (process_name_command_arg(warray[1], aliases) == 0)
        return 0;
    display_single_alias(warray[1], aliases);
    return 0;
}

int handle_unalias_command(char **warray, alias_t *aliases)
{
    if (!warray || !aliases)
        return 84;
    if (warray[1] == NULL) {
        printv("unalias: Too few arguments.\n", 2);
        return 1;
    }
    for (int i = 1; warray[i] != NULL; i++)
        remove_alias(aliases, warray[i]);
    return 0;
}

char **substitute_aliases(char **warray, alias_t *aliases)
{
    char *alias_cmd;
    char **new_args;

    if (!warray || !aliases || !warray[0])
        return warray;
    alias_cmd = get_alias_command(aliases, warray[0]);
    if (!alias_cmd)
        return warray;
    new_args = my_str_to_warray(alias_cmd, " \t\n");
    if (!new_args)
        return warray;
    my_free_warray(warray);
    return new_args;
}
