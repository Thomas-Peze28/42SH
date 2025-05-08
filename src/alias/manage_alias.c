/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** manage_alias
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "workspace.h"

alias_t *init_aliases(int capacity)
{
    alias_t *aliases = malloc(sizeof(alias_t));

    if (!aliases)
        return NULL;
    aliases->names = calloc(capacity, sizeof(char *));
    aliases->commands = calloc(capacity, sizeof(char *));
    if (!aliases->names || !aliases->commands) {
        free(aliases->names);
        free(aliases->commands);
        free(aliases);
        return NULL;
    }
    aliases->count = 0;
    aliases->capacity = capacity;
    return aliases;
}

void add_alias(alias_t *aliases, char *name, char *command)
{
    if (!aliases || !name || !command)
        return;
    for (int i = 0; i < aliases->count; i++) {
        if (my_strcmp(aliases->names[i], name)) {
            free(aliases->commands[i]);
            aliases->commands[i] = my_strdup(command);
            return;
        }
    }
    if (aliases->count < aliases->capacity) {
        aliases->names[aliases->count] = my_strdup(name);
        aliases->commands[aliases->count] = my_strdup(command);
        aliases->count++;
    }
}

static void remove_alias_at(alias_t *aliases, int i, char *name)
{
    if (my_strcmp(aliases->names[i], name)) {
        free(aliases->names[i]);
        free(aliases->commands[i]);
        for (int j = i; j < aliases->count - 1; j++) {
            aliases->names[j] = aliases->names[j + 1];
            aliases->commands[j] = aliases->commands[j + 1];
        }
        aliases->count--;
        aliases->names[aliases->count] = NULL;
        aliases->commands[aliases->count] = NULL;
        return;
    }
}

void remove_alias(alias_t *aliases, char *name)
{
    if (!aliases || !name)
        return;
    for (int i = 0; i < aliases->count; i++) {
        remove_alias_at(aliases, i, name);
    }
}

char *get_alias_command(alias_t *aliases, char *name)
{
    if (!aliases || !name)
        return NULL;
    for (int i = 0; i < aliases->count; i++) {
        if (my_strcmp(aliases->names[i], name)) {
            return aliases->commands[i];
        }
    }
    return NULL;
}

void display_aliases(alias_t *aliases)
{
    if (!aliases)
        return;
    for (int i = 0; i < aliases->count; i++) {
        printv(aliases->names[i], 1);
        printv("='", 1);
        printv(aliases->commands[i], 1);
        printv("'\n", 1);
    }
}
