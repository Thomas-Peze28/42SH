/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_strstr
*/

#include "../include/my.h"
#include <stdlib.h>

static char *create_empty_substr(void)
{
    char *substr = malloc(1);

    if (!substr)
        return NULL;
    substr[0] = '\0';
    return substr;
}

static char *copy_substring(char *str, int start, int end)
{
    char *substr = malloc(sizeof(char) * (end - start + 1));
    int i = 0;

    if (!substr)
        return NULL;
    while (start < end) {
        substr[i] = str[start];
        start++;
        i++;
    }
    substr[i] = '\0';
    return substr;
}

char *my_substr(char *str, int start, int end)
{
    int len = my_strlen(str);

    if (start < 0)
        start = 0;
    if (end > len)
        end = len;
    if (start >= end)
        return create_empty_substr();
    return copy_substring(str, start, end);
}

int my_strcmp(char *str1, char *str2)
{
    int j = 0;

    if (!str1 || !str2)
        return 0;
    while (str2[j] != '\0') {
        if (str1[j] == '\0' || str1[j] != str2[j])
            return 0;
        j++;
    }
    return 1;
}

int my_strstr(char *str, char *to_find)
{
    int i = 0;
    int len_find = my_strlen(to_find);
    char *substr;

    while (str[i] != '\0') {
        substr = my_substr(str, i, i + len_find);
        if (my_strcmp(substr, to_find)) {
            free(substr);
            return 1;
        }
        i++;
        free(substr);
    }
    return 0;
}
