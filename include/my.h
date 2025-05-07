/*
** EPITECH PROJECT, 2024
** my header
** File description:
** header file that contains the prototypes of
** the functions exposed by your libmy.a
*/

#ifndef MY_H
    #define MY_H
    #include <stddef.h>

typedef struct indices_s {
    int i;
    int j;
    int k;
} indices_t;

// Print functions
void my_putchar(char c);
void my_putstr(char *str);
void my_putnbr(int nb);

// String functions
int my_strlen(char *str);
int my_tablen(char **tab);
char *my_revstr(char *str);
int my_isprintable(char *str);
int my_strcmp(char *str1, char *str2);
int my_strcmpn(char *str1, char *str2, int n);
char *my_substr(char *str, int start, int end);
int my_str_is_same(char *str1, char *str2);
int my_strstr(char *str, char *to_find);
char *my_strcat(char *dest, char *src);
char *my_strcpy(char *dest, char *src);
char *my_strdup(char *src);
int my_count_words(char *str, char *separator);
int my_is_in_str(char c, char *str);
void my_free_warray(char **warray);
char **my_str_to_warray(char *str, char *separator);
int my_strncmp(char *str1, char *str2, int n);

// Number functions
int my_nbrlen(int nb);
int my_sqrt(int nb);
int my_abs(int nb);
int my_pow(int nb, int p);
int my_atoi(char *str);

// Sort functions


// Manage functions
int no_int_overflow(int nb);

int my_is_alphanum(char *str);
int get_line_ncurses(char **buffer);
char *execve_and_get_stdout(char *path, char **argv, char **envp);
void printv(char *text, int status);
int my_which(char **warray, char **env);
int print_42sh_ascii(void);
int process_env_command(char **env, char **warray);
#endif /* MY_H */
