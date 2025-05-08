/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** alias_commands
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "workspace.h"

static void extract_name_command(char *arg, char **name, char **command)
{
    *name = NULL;
    *command = NULL;
    *name = arg;
}

int process_name_command_arg(char *arg, alias_t *aliases)
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

void display_single_alias(char *alias_name, alias_t *aliases)
{
    char *command = get_alias_command(aliases, alias_name);

    if (command) {
        printv(command, 1);
        printv("\n", 1);
    }
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
