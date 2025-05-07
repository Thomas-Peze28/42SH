/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

char *get_full_path(char *str, char *path)
{
    char *fpath = malloc(strlen(path) + strlen(str) + 2);

    if (fpath == NULL)
        return NULL;
    my_strcpy(fpath, path);
    my_strcat(fpath, "/");
    my_strcat(fpath, str);
    fpath[strlen(path) + strlen(str) + 1] = '\0';
    if (access(fpath, X_OK) == 0)
        return fpath;
    free(fpath);
    return NULL;
}

char **get_path_env(myshell_t *shell)
{
    char *PATH = my_getenv(shell, "PATH");
    char **res = NULL;

    if (PATH == NULL)
        return NULL;
    res = my_split(PATH, ':');
    free(PATH);
    return res;
}

char *extract_commands_path(myshell_t *shell, char *commands)
{
    char **PATH = get_path_env(shell);
    char *res = NULL;

    if (PATH == NULL)
        return NULL;
    for (int i = 0; PATH[i] != NULL; i++){
        res = get_full_path(commands, PATH[i]);
        if (res != NULL)
            break;
    }
    my_free_list(PATH);
    return res;
}
