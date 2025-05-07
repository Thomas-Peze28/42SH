/*
** EPITECH PROJECT, 2025
** base_folder
** File description:
** test_my_str_to_warray
*/

#include <stdlib.h>
#include "../include/my.h"

void my_free_warray(char **warray)
{
    for (int i = 0; warray[i] != NULL; i++)
        free(warray[i]);
    free(warray);
}

static void skip_separator(char **str, char *separator)
{
    while (my_is_in_str(**str, separator) == 1)
        (*str)++;
}

static int get_word_len(char *str, char *separator)
{
    int len = 0;

    while (str[len] != '\0' && my_is_in_str(str[len], separator) == 0)
        len++;
    return len;
}

static char *extract_word(char *str, int len)
{
    char *word = malloc(sizeof(char) * (len + 1));

    if (word == NULL)
        return NULL;
    for (int i = 0; i < len; i++)
        word[i] = str[i];
    word[len] = '\0';
    return word;
}

static int fill_warray(char **warray, char *str, char *separator, int nb_words)
{
    int len;

    for (int i = 0; i < nb_words; i++) {
        skip_separator(&str, separator);
        len = get_word_len(str, separator);
        warray[i] = extract_word(str, len);
        if (warray[i] == NULL)
            return 0;
        str += len;
    }
    return 1;
}

char **my_str_to_warray(char *str, char *separator)
{
    int nb_words = my_count_words(str, separator);
    char **warray = malloc(sizeof(char *) * (nb_words + 1));

    if (warray == NULL)
        return NULL;
    warray[nb_words] = NULL;
    if (fill_warray(warray, str, separator, nb_words) == 0) {
        my_free_warray(warray);
        return NULL;
    }
    return warray;
}
