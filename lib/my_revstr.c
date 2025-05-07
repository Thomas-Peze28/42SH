/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_revstr
*/

#include "../include/my.h"

char *my_revstr(char *str)
{
    int i = 0;
    int j = my_strlen(str) - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
    return str;
}
