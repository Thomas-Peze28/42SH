/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_iota
*/

#include "../include/my.h"
#include <stdlib.h>

int my_nbrlen(int nb)
{
    int i = 0;

    if (nb == 0)
        return 1;
    if (nb < 0) {
        i++;
        nb = -nb;
    }
    while (nb != 0) {
        nb = nb / 10;
        i++;
    }
    return i;
}
