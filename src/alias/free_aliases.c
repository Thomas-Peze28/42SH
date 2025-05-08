/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-42sh-pierric.buchez
** File description:
** free_aliases
*/

#include <stdlib.h>
#include "workspace.h"
#include "my.h"

static void free_aliases_content(alias_t *aliases)
{
    for (int i = 0; i < aliases->count; i++) {
        if (aliases->names[i])
            free(aliases->names[i]);
        if (aliases->commands[i])
            free(aliases->commands[i]);
    }
}

void free_aliases(alias_t *aliases)
{
    if (!aliases)
        return;
    if (aliases->names && aliases->commands) {
        free_aliases_content(aliases);
    }
    if (aliases->names)
        free(aliases->names);
    if (aliases->commands)
        free(aliases->commands);
    free(aliases);
}
