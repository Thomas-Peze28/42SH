/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** free
*/

#include <stdlib.h>

int free_all(int ret_code, char *line, char **warray)
{
    int i = 0;

    if (warray != NULL) {
        for (i = 0; warray[i] != NULL; i++) {
            free(warray[i]);
        }
        free(warray);
    }
    if (line != NULL) {
        free(line);
    }
    return ret_code;
}

void free_divise_path(char **paths)
{
    int i = 0;

    if (paths) {
        for (i = 0; paths[i] != NULL; i++) {
            free(paths[i]);
        }
        free(paths);
    }
}
