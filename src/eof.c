/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/

#include "mysh.h"

static void put_str_eof(myshell_t *shell, char *str)
{
    int buff_size = 0;
    int new_str_size = my_strlen(str);
    char *tmpbuffer = NULL;

    if (shell->stdout != NULL){
        buff_size = my_strlen(shell->stdout);
        tmpbuffer = shell->stdout;
    }
    shell->stdout = malloc(buff_size + new_str_size + 1);
    if (shell->stdout == NULL){
        shell->stdout = tmpbuffer;
        return;
    }
    if (tmpbuffer != NULL)
        my_strcpy(shell->stdout, tmpbuffer);
    if (tmpbuffer != NULL)
        my_strcat(shell->stdout, str);
    else
        my_strcpy(shell->stdout, str);
    free(tmpbuffer);
}

static int read_eof_line(char **buffer)
{
    int reads = 0;

    if (isatty(0) && isatty(1))
        write(1, "? ", 2);
    if (isatty(0) || isatty(1))
        reads = getlines_sub(buffer, true);
    else
        reads = get_line_ncurses(buffer);
    return reads;
}

void parse_eof(myshell_t *shell, char *eof)
{
    int reads = 0;
    char *buffer = NULL;

    free(shell->stdout);
    shell->stdout = NULL;
    if (eof == NULL)
        return;
    while (reads != -1){
        reads = read_eof_line(&buffer);
        if (reads == -1 || reads < 1)
            continue;
        if (is_good_eof(eof, buffer) == true)
            break;
        put_str_eof(shell, buffer);
    }
    if (reads > 0)
        free(buffer);
}
