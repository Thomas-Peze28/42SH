/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static unsigned int calc_result(myshell_t *shell)
{
    char *fpath = NULL;
    unsigned int res = 0;

    for (int i = 1; shell->splitted[i] != NULL; i++){
        fpath = extract_commands_path(shell, shell->splitted[i]);
        if (fpath != NULL){
            res += (my_strlen(fpath) + 1);
            free(fpath);
        } else
            res += (my_strlen(shell->splitted[i]) + 22);
    }
    return res;
}

static char *get_which_result(myshell_t *shell, unsigned int len)
{
    char *res = malloc(len + 1);
    char *fpath = NULL;

    if (res == NULL)
        return NULL;
    res[0] = '\0';
    for (int i = 1; shell->splitted[i] != NULL; i++){
        fpath = extract_commands_path(shell, shell->splitted[i]);
        if (fpath != NULL){
            my_strcat(res, fpath);
            my_strcat(res, "\n");
            free(fpath);
            fpath = NULL;
        } else {
            my_strcat(res, shell->splitted[i]);
            my_strcat(res, ": Command not found.\n");
        }
    }
    return res;
}

static unsigned char print_which(myshell_t *shell, char *res)
{
    if (res == NULL)
        return 84;
    if (shell->piped == true) {
        free(shell->stdout);
        shell->stdout = res;
    } else {
        if (!isatty(0) || !isatty(1))
            printf("%s", res);
        else
            printw("%s", res);
        free(shell->stdout);
        shell->stdout = NULL;
        free(res);
    }
    return 0;
}

int my_which(myshell_t *shell)
{
    int len = my_list_len(shell->splitted);
    int result_len = calc_result(shell);
    char *res = NULL;

    if (len < 2){
        printw("which: Too few arguments.\n");
        return -2;
    }
    res = get_which_result(shell, result_len);
    if (print_which(shell, res) == 0){
        shell->status = 0;
        return 0;
    }
    return 0;
}
