/*
** EPITECH PROJECT, 2025
** base_folder
** File description:
** count_nb_words
*/

#include "../include/my.h"

int my_count_words(char *str, char *separator)
{
    int nb_words = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (my_is_in_str(str[i], separator) == 0 &&
                my_is_in_str(str[i + 1], separator) == 1) {
            nb_words++;
        }
        i++;
    }
    if (str[i - 1] != '\0' && my_is_in_str(str[i - 1], separator) == 0) {
        nb_words++;
    }
    return nb_words;
}
