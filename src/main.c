/*
** EPITECH PROJECT, 2024
** main for NOM_BINAIRE project
** File description:
** main function
*/

#include "workspace.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ncurses.h>

int verify_path(char **env, char **warray, int i)
{
    char **path = NULL;
    int result = 84;

    if (env[i][0] == 'P' && env[i][1] == 'A' &&
        env[i][2] == 'T' && env[i][3] == 'H' &&
        env[i][4] == '=') {
        path = divise_path(env[i]);
        if (path == NULL)
            return 84;
        result = search_command(path, warray, env);
        free_divise_path(path);
        return result;
    }
    return 1;
}

int process_env_command(char **env, char **warray)
{
    int i = 0;
    int result = 84;

    if (env == NULL)
        return 84;
    for (; env[i] != NULL; i++) {
        result = verify_path(env, warray, i);
        if (result == 0)
            return 0;
        if (result == 84)
            return 84;
    }
    return result;
}

static int handle_input_error(char *line, char **warray)
{
    if (line != NULL)
        free(line);
    if (warray != NULL)
        return free_all(84, NULL, warray);
    return -1;
}

static int process_command(char **warray_command, char ***env,
    int i, history_t *history)
{
    int resultat = 0;
    char **warray = my_str_to_warray(warray_command[i], " \t\n");

    if (warray == NULL)
        return free_all(84, NULL, warray);
    if (my_strcmp(warray[0], "exit") && my_strlen(warray[0]) <= 4) {
        free_all(0, NULL, warray);
        return 0;
    }
    resultat = execute_piped_commands(warray_command[i], env);
    if (resultat == -1) {
        resultat = gest_comm(warray, env, history);
    }
    return free_all(resultat, NULL, warray);
}

static char *get_line(history_t *history)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read_line;

    if (!isatty(0) || !isatty(1))
        read_line = getline(&line, &len, stdin);
    else
        read_line = get_line_ncurses(&line, history);
    if (read_line == -1)
        return NULL;
    if (read_line > 1)
        add_to_history(history, line);
    return line;
}

static int process_iteration(char ***env, history_t *history)
{
    char *line = NULL;
    char **warray_command = NULL;
    int result;

    line = get_line(history);
    if (line == NULL)
        return handle_input_error(line, warray_command);
    warray_command = my_str_to_warray(line, ";");
    for (int i = 0; warray_command[i] != NULL; i++) {
        result = process_command(warray_command, env, i, history);
        if (result == -1)
            return handle_input_error(line, warray_command);
    }
    handle_exit(line, warray_command, env, history);
    return free_all(result, line, warray_command);
}

static int verify_env_history(char **env, history_t *history)
{
    if (!env || !history) {
        if (env)
            free_env(env);
        if (history)
            free_history(history);
        return 1;
    }
    return 0;
}

int mysh(int result, char **env_original)
{
    char **env = dup_env(env_original);
    history_t *history = init_history(100);

    if (verify_env_history(env, history))
        return 84;
    if (!isatty(STDIN_FILENO)) {
        result = process_iteration(&env, history);
        while (result != -1)
            result = process_iteration(&env, history);
        free_env(env);
        free_history(history);
        return result == -1 ? 0 : result;
    }
    while (result != -1) {
        result = process_iteration(&env, history);
    }
    free_env(env);
    free_history(history);
    return result;
}

void init_ncurses(void)
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    print_42sh_ascii();
}

int main(int argc, char **argv, char **env)
{
    int result = 0;

    if (isatty(0) && isatty(1)) {
        init_ncurses();
    }
    if (!env)
        return 84;
    if (argc != 1 || argv[1] != NULL)
        return 84;
    result = mysh(0, env);
    return result;
}
