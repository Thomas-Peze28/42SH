/*
** EPITECH PROJECT, 2024
** header for workspace
** File description:
** header file that contains the prototypes of
** the functions used in the workspace
*/

#ifndef WORKSPACE_H
    #define WORKSPACE_H

    #include <sys/wait.h>

typedef struct seg_info_s {
    int start;
    int id_path;
} seg_info_t;

typedef struct pipe_data_s {
    int pipes[10][2];
    pid_t pids[11];
    int cmd_count;
} pipe_data_t;

typedef struct pipe_info {
    int *in_fd;
    int *out_fd;
    int pipes[10][2];
    int pos;
    int count;
} pipe_info_t;

typedef struct redirection_s {
    int type;
    char *file;
    int original_fd;
} redirection_t;

typedef struct history_s {
    char **commands;
    int count;
    int capacity;
} history_t;

typedef struct alias_s {
    char **names;
    char **commands;
    int count;
    int capacity;
} alias_t;

void free_eha(char **env, history_t *history, alias_t *aliases);

alias_t *init_aliases(int capacity);
void add_alias(alias_t *aliases, char *name, char *command);
void remove_alias(alias_t *aliases, char *name);
char *get_alias_command(alias_t *aliases, char *name);
void display_aliases(alias_t *aliases);
void free_aliases(alias_t *aliases);
int handle_alias_command(char **warray, alias_t *aliases);
int handle_unalias_command(char **warray, alias_t *aliases);
char **substitute_aliases(char **warray, alias_t *aliases);

history_t *init_history(int capacity);
void add_to_history(history_t *history, char *command);
void display_history(history_t *history);
void free_history(history_t *history);
int handle_history_command(char **warray, history_t *history);

void free_env(char **env);
int free_all(int ret_code, char *line, char **warray);
void free_divise_path(char **paths);
int func_cd(char **warray, char ***env);
int func_env(char **warray, char **env);
int func_setenv_unsetenv(char **warray, char ***env);
char **divise_path(char *envline);
void replace_env(char ***env, char **new_env);
char **dup_env(char **env_original);
int search_command(char **path, char **command, char **env);
int try_exec_command(char *dir, char **command, char **env);
char **func_setenv(char **warray, char **env, int len_warray);
int change_dir_env(char ***env, char *oldpwd);
char **func_unsetenv(char **warray, char **env, int len_warray);
int handle_exit(char **warray, char ***env,
    history_t *history, alias_t *aliases);
int execute_piped_commands(char *warray, char ***env);
int gest_comm(char **warray, char ***env,
    history_t *history, alias_t *aliases);

void free_list_commands(char ***list_commands);
int verif_pip(char **warray, int nb_pipe);
char ***create_list_commands(char **warray, int nb_pipe, char **env);
int check_empty_command(char *command);
pid_t fork_and_execute(char **args, int in_fd, int out_fd, char **env);
int run_commands(char ***commands, pipe_data_t *data, char **env);
int setup_pipes(pipe_data_t *data);
int execute_single_command(char **cmd, char **env);

int handle_redirections(char **warray, redirection_t *redir);
void cleanup_redirection(redirection_t *redir);
int setup_redirection(redirection_t *redir);
int exec_with_redirection(char *dir, char **command,
    char **env, redirection_t *redir);

#endif /* WORKSPACE_H */
