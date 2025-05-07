/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** func_env
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "workspace.h"
#include "my.h"

void replace_env(char ***env, char **new_env)
{
    if (*env != NULL && new_env != *env) {
        free_env(*env);
        *env = new_env;
    }
}

static char **free_dup_env(char **env_copy, int i)
{
    for (int j = 0; j < i; j++)
        free(env_copy[j]);
    free(env_copy);
    return NULL;
}

char **dup_env(char **env_original)
{
    char **env_copy = NULL;
    int size = 0;
    int i;

    while (env_original[size] != NULL)
        size++;
    env_copy = malloc(sizeof(char *) * (size + 1));
    if (!env_copy)
        return NULL;
    for (i = 0; i < size; i++) {
        env_copy[i] = my_strdup(env_original[i]);
        if (!env_copy[i]) {
            return free_dup_env(env_copy, i);
        }
    }
    env_copy[size] = NULL;
    return env_copy;
}

int func_env(char **warray, char **env)
{
    int i = 0;

    if (env == NULL)
        return 84;
    if (warray[1] != NULL) {
        printv("env: too many arguments.\n", 2);
        return 84;
    }
    for (i = 0; env[i] != NULL; i++) {
        printv(env[i], 1);
        printv("\n", 1);
    }
    return 0;
}
