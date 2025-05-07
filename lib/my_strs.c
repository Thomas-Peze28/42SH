/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell1-etienne.pouille
** File description:
** my_strs
*/

#include <stdlib.h>

char *my_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i] != '\0')
        i++;
    while (src[j] != '\0') {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strdup(char *src)
{
    char *dest;
    int i = 0;

    if (src == NULL)
        return NULL;
    while (src[i] != '\0')
        i++;
    dest = malloc(sizeof(char) * (i + 1));
    if (dest == NULL)
        return NULL;
    i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
