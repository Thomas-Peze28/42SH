/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** func_setenv_unsetenv
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my.h"
#include "workspace.h"

void free_env(char **env)
{
    int i;

    if (env == NULL)
        return;
    for (i = 0; env[i] != NULL; i++) {
        free(env[i]);
    }
    free(env);
}

static char *create_env_var(char **warray, int len_warray)
{
    char *new_var = NULL;
    int var_len = my_strlen(warray[1]);
    int val_len = (len_warray == 3) ? my_strlen(warray[2]) : 0;

    new_var = malloc(sizeof(char) * (var_len + val_len + 2));
    if (new_var == NULL)
        return NULL;
    my_strcpy(new_var, warray[1]);
    my_strcat(new_var, "=");
    if (len_warray == 3)
        my_strcat(new_var, warray[2]);
    return new_var;
}

static int is_matching_env_var(char *env_var, char *var_name)
{
    int var_len = my_strlen(var_name);

    return my_strcmpn(env_var, var_name, var_len) &&
        env_var[var_len] == '=';
}

static char **process_env_vars(char **env,
    char *new_var, char *var_name, int *found)
{
    int i = 0;
    int env_size = my_tablen(env);
    char **new_env = malloc(sizeof(char *) * (env_size + 2));

    if (new_env == NULL)
        return NULL;
    for (i = 0; env[i] != NULL; i++) {
        if (is_matching_env_var(env[i], var_name)) {
            new_env[i] = my_strdup(new_var);
            *found = 1;
        } else {
            new_env[i] = my_strdup(env[i]);
        }
    }
    new_env[i] = NULL;
    return new_env;
}

static char **build_new_env(char **env, char *new_var, char *var_name)
{
    char **new_env = NULL;
    int found = 0;
    int i;

    new_env = process_env_vars(env, new_var, var_name, &found);
    if (!found) {
        for (i = 0; new_env[i] != NULL; i++);
        new_env[i] = my_strdup(new_var);
        new_env[i + 1] = NULL;
    }
    return new_env;
}

char **func_setenv(char **warray, char **env, int len_warray)
{
    char *new_var = NULL;
    char **new_env = NULL;

    if (len_warray == 1)
        return func_env(warray, env) == 84 ? NULL : env;
    if (len_warray >= 4) {
        printv("setenv: Too many arguments.\n", 2);
        return env;
    }
    new_var = create_env_var(warray, len_warray);
    if (new_var == NULL)
        return env;
    new_env = build_new_env(env, new_var, warray[1]);
    free(new_var);
    return (new_env == NULL) ? env : new_env;
}

static char **remove_env_var(char **env, char *var_name, int var_len)
{
    char **new_env = NULL;
    int env_size = my_tablen(env);
    int i = 0;
    int j = 0;

    new_env = malloc(sizeof(char *) * (env_size + 1));
    if (new_env == NULL)
        return env;
    for (i = 0; env[i] != NULL; i++) {
        if (!(my_strcmpn(env[i], var_name, var_len) &&
            env[i][var_len] == '=')) {
            new_env[j] = my_strdup(env[i]);
            j++;
        }
    }
    new_env[j] = NULL;
    return new_env;
}

char **func_unsetenv(char **warray, char **env, int len_warray)
{
    int var_len = 0;

    if (len_warray <= 1) {
        printv("unsetenv: Too few arguments.\n", 2);
        return env;
    }
    if (len_warray >= 3) {
        printv("unsetenv: Too many arguments.\n", 2);
        return env;
    }
    var_len = my_strlen(warray[1]);
    return remove_env_var(env, warray[1], var_len);
}

int func_setenv_unsetenv(char **warray, char ***env)
{
    int len_warray = 0;
    char **new_env = NULL;

    for (len_warray = 0; warray[len_warray] != NULL; len_warray++);
    if (warray == NULL || env == NULL)
        return 84;
    if (len_warray != 1 && my_is_alphanum(warray[1]) == 0) {
        printv("setenv: Variable name must ", 2);
        printv("contain alphanumeric characters.\n", 2);
        return 0;
    }
    if (my_strcmp(warray[0], "setenv")) {
        new_env = func_setenv(warray, *env, len_warray);
    } else if (my_strcmp(warray[0], "unsetenv")) {
        new_env = func_unsetenv(warray, *env, len_warray);
    }
    if (new_env != NULL && new_env != *env)
        replace_env(env, new_env);
    return 0;
}
