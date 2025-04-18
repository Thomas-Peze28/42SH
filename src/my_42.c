/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

int my_42(myshell_t *shell)
{
    char *str = "The universe and everything\n";

    if (shell->piped == true){
        free(shell->stdout);
        shell->stdout = malloc(strlen(str) + 1);
        if (shell->stdout != NULL)
            my_strcpy(shell->stdout, str);
    } else
        my_putstr(str);
    shell->status = 42;
    return 0;
}
