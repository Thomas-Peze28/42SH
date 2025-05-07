/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** div_path
*/

#include <stdlib.h>
#include "my.h"
#include "workspace.h"

int len_path(char *envline)
{
    int len = 0;
    int i = 5;

    if (envline == NULL)
        return -1;
    for (; envline[i] != '\0'; i++) {
        if (envline[i] == ':')
            len++;
    }
    return len + 1;
}

char *put_in(int id_char, int i, char *envline)
{
    int j = 0;
    char *word = malloc(sizeof(char) * (id_char + 1));

    if (!word)
        return NULL;
    for (j = 0; j < id_char; j++) {
        word[j] = envline[i - id_char + j];
    }
    word[id_char] = '\0';
    return word;
}

static void add_segment(char **path, char *envline, int end, seg_info_t *info)
{
    int len = end - info->start;

    path[info->id_path] = put_in(len, end, envline);
    if (!path[info->id_path])
        return;
    info->id_path++;
    info->start = end + 1;
}

char **divise_path(char *envline)
{
    int total = len_path(envline);
    char **path;
    seg_info_t info = {.start = 5, .id_path = 0};
    int i = info.start;

    if (total == -1)
        return NULL;
    path = malloc(sizeof(char *) * (total + 1));
    if (!path)
        return NULL;
    while (envline[i] != '\0') {
        if (envline[i] == ':')
            add_segment(path, envline, i, &info);
        i++;
    }
    if (i - info.start > 0)
        add_segment(path, envline, i, &info);
    path[info.id_path] = NULL;
    return path;
}
