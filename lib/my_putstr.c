/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_putstr
*/

#include <unistd.h>
# include "../include/my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        my_putchar(str[i]);
}
