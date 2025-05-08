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

static char *extract_name(char *arg, char *equals)
{
    int name_len = equals - arg;
    char *name = malloc(name_len + 1);

    if (!name)
        return NULL;
    strncpy(name, arg, name_len);
    name[name_len] = '\0';
    return name;
}

static char *build_command_with_equals(char **args, char *cmd_start)
{
    int cmd_len = strlen(cmd_start) + 1;
    char *command = NULL;
    int i = 0;

    for (i = 2; args[i]; i++)
        cmd_len += strlen(args[i]) + 1;
    command = malloc(cmd_len);
    if (!command)
        return NULL;
    strcpy(command, cmd_start);
    for (i = 2; args[i]; i++) {
        strcat(command, " ");
        strcat(command, args[i]);
    }
    return command;
}

static int handle_alias_with_equals(char **args, alias_t *aliases)
{
    char *equals = strchr(args[1], '=');
    char *name = extract_name(args[1], equals);
    char *cmd_start = equals + 1;
    char *command = NULL;

    if (!name)
        return 84;
    command = build_command_with_equals(args, cmd_start);
    if (!command) {
        free(name);
        return 84;
    }
    add_alias(aliases, name, command);
    free(name);
    free(command);
    return 0;
}

static char *build_command_without_equals(char **args)
{
    int cmd_len = 0;
    char *command = NULL;
    int i = 0;

    for (i = 2; args[i]; i++)
        cmd_len += strlen(args[i]) + 1;
    command = malloc(cmd_len);
    if (!command)
        return NULL;
    command[0] = '\0';
    for (i = 2; args[i]; i++) {
        if (i > 2)
            strcat(command, " ");
        strcat(command, args[i]);
    }
    return command;
}

static int handle_alias_without_equals(char **args, alias_t *aliases)
{
    char *name = args[1];
    char *command = build_command_without_equals(args);

    if (!command)
        return 84;
    add_alias(aliases, name, command);
    free(command);
    return 0;
}

int handle_alias_command(char **args, alias_t *aliases)
{
    char *equals = NULL;

    if (!args[1]) {
        display_aliases(aliases);
        return 0;
    }
    equals = strchr(args[1], '=');
    if (!args[2] && !equals) {
        display_single_alias(args[1], aliases);
        return 0;
    }
    if (equals)
        return handle_alias_with_equals(args, aliases);
    else
        return handle_alias_without_equals(args, aliases);
}
