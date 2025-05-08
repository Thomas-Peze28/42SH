/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** func_cd
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "workspace.h"

static char *get_home(char **env)
{
    int i = 0;
    char *home = NULL;

    if (env == NULL)
        return NULL;
    for (i = 0; env[i] != NULL; i++) {
        if (my_strstr(env[i], "HOME=")) {
            home = my_substr(env[i], 5, my_strlen(env[i]));
            return home;
        }
    }
    return NULL;
}

static int handle_home_directory(char **env)
{
    char *home = get_home(env);

    if (home == NULL) {
        printv("cd: HOME not set.\n", 2);
        return 84;
    }
    if (chdir(home) == -1) {
        printv("cd: can't change to home directory.\n", 2);
        free(home);
        return 84;
    }
    free(home);
    return 0;
}

char *previous_dir(char **env)
{
    int i = 0;
    char *oldpwd = NULL;

    if (env == NULL)
        return NULL;
    for (i = 0; env[i] != NULL; i++) {
        if (my_strstr(env[i], "OLDPWD=")) {
            oldpwd = my_substr(env[i], 7, my_strlen(env[i]));
            return oldpwd;
        }
    }
    return NULL;
}

int func_perv_dir(char **env)
{
    char *previous_directory = previous_dir(env);

    if (previous_directory == NULL) {
        printv("cd: No previous directory.\n", 2);
        return 84;
    }
    if (chdir(previous_directory) == -1) {
        free(previous_directory);
        printv("cd: can't change to previous directory.\n", 2);
        return 84;
    }
    free(previous_directory);
    return 0;
}

int handle_tilde(char **warray, char **env)
{
    char *home = get_home(env);
    char *directory = malloc(sizeof(char) * (my_strlen(home) +
        my_strlen(warray[1]) + 1));

    if (home == NULL) {
        printv("cd: HOME not set.\n", 2);
        return 84;
    }
    if (directory == NULL)
        return 84;
    my_strcpy(directory, home);
    free(home);
    my_strcat(directory, &warray[1][1]);
    if (chdir(directory) == -1) {
        printv("cd: can't change to home directory.\n", 2);
        free(directory);
        return 84;
    }
    free(directory);
    return 0;
}

int func_cd(char **warray, char ***env)
{
    int len = 0;

    while (warray[len] != NULL)
        len++;
    if (len > 2) {
        printv("cd: too many arguments.\n", 2);
        return 0;
    }
    if (warray[1] == NULL || (my_strcmp(warray[1], "~") &&
        my_strlen(warray[1]) == 1))
        return handle_home_directory(*env);
    if (my_strcmp(warray[1], "-"))
        return func_perv_dir(*env);
    if (my_strcmp(warray[1], "~"))
        return handle_tilde(warray, *env);
    if (chdir(warray[1]) == -1) {
        printv(warray[1], 2);
        printv(": Not a directory.\n", 2);
    }
    return 0;
}
