/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_putnbr
*/

#include "../include/my.h"

int no_int_overflow(int nb)
{
    if (nb >= -2147483648 && nb <= 2147483647)
        return 1;
    return 0;
}

void my_putnbr(int nb)
{
    if (no_int_overflow(nb) == 0)
        return;
    if (nb < 0) {
        my_putchar('-');
        nb = -nb;
    }
    if (nb >= 10) {
        my_putnbr(nb / 10);
        my_putchar(nb % 10 + '0');
    } else {
        my_putchar(nb + '0');
    }
}
