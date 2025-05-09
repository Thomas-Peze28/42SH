/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** create_alias
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "workspace.h"

static char *extract_name(char *arg, char *equals)
{
    int name_len = equals - arg;
    char *name = NULL;

    name = malloc(name_len + 1);
    if (!name)
        return NULL;
    strncpy(name, arg, name_len);
    name[name_len] = '\0';
    return name;
}

static char *combine_args(char **args, int start_idx)
{
    int cmd_len = 0;
    char *command = NULL;
    int i = 0;

    for (i = start_idx; args[i]; i++)
        cmd_len += my_strlen(args[i]) + 1;
    command = malloc(cmd_len + 1);
    if (!command)
        return NULL;
    command[0] = '\0';
    for (i = start_idx; args[i]; i++) {
        if (i > start_idx)
            my_strcat(command, " ");
        my_strcat(command, args[i]);
    }
    return command;
}

static char *append_command_parts(char *initial, char **warray, int start)
{
    char *temp = NULL;
    char *command = NULL;
    int i = 0;

    command = my_strdup(initial);
    if (!command)
        return NULL;
    for (i = start; warray[i]; i++) {
        temp = command;
        command = malloc(my_strlen(temp) + my_strlen(warray[i]) + 2);
        if (!command) {
            free(temp);
            return NULL;
        }
        my_strcpy(command, temp);
        my_strcat(command, " ");
        my_strcat(command, warray[i]);
        free(temp);
    }
    return command;
}

static int finalize_alias(char *name, char *command, alias_t *aliases)
{
    add_alias(aliases, name, command);
    free(name);
    free(command);
    return 0;
}

static int handle_alias_with_equals(char **warray, alias_t *aliases)
{
    char *equals_pos = strchr(warray[1], '=');
    char *name = NULL;
    char *initial_cmd = NULL;
    char *command = NULL;

    name = extract_name(warray[1], equals_pos);
    if (!name)
        return 84;
    initial_cmd = my_strdup(equals_pos + 1);
    if (!initial_cmd) {
        free(name);
        return 84;
    }
    command = append_command_parts(initial_cmd, warray, 2);
    free(initial_cmd);
    if (!command) {
        free(name);
        return 84;
    }
    return finalize_alias(name, command, aliases);
}

static int handle_alias_without_equals(char **warray, alias_t *aliases)
{
    char *name = warray[1];
    char *command = NULL;

    command = combine_args(warray, 2);
    if (!command)
        return 84;
    add_alias(aliases, name, command);
    free(command);
    return 0;
}

int create_alias_from_args(char **warray, alias_t *aliases)
{
    char *equals_pos = NULL;

    if (!warray[1])
        return 0;
    equals_pos = strchr(warray[1], '=');
    if (equals_pos)
        return handle_alias_with_equals(warray, aliases);
    if (warray[2])
        return handle_alias_without_equals(warray, aliases);
    return 0;
}
