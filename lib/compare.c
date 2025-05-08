/*
** EPITECH PROJECT, 2025
** lib
** File description:
** compare
*/

#include "../include/my.h"

int my_strcmpn(char *str1, char *str2, int n)
{
    int j = 0;

    while (str2[j] != '\0' && j < n) {
        if (str1[j] != str2[j])
            return 0;
        j++;
    }
    return 1;
}

int my_strncmp(char *str1, char *str2, int n)
{
    int i = 0;

    while (i < n) {
        if (str1[i] != str2[i] || str1[i] == '\0' || str2[i] == '\0')
            return str1[i] - str2[i];
        i++;
    }
    return 0;
}
