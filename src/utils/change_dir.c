/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** change_dir
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "workspace.h"

int change_dir_env(char ***env, char *oldpwd)
{
    char *pwd = getcwd(NULL, 0);
    char *oldpwd_var[] = {"setenv", "OLDPWD", oldpwd, NULL};
    char *pwd_var[] = {"setenv", "PWD", pwd, NULL};

    if (pwd == NULL || oldpwd_var[2] == NULL || pwd_var[2] == NULL)
        return 84;
    func_setenv_unsetenv(oldpwd_var, env);
    func_setenv_unsetenv(pwd_var, env);
    free(pwd);
    free(oldpwd);
    return 0;
}
