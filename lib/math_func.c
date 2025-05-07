/*
** EPITECH PROJECT, 2025
** lib
** File description:
** math_func
*/

int my_abs(int nb)
{
    if (nb < 0)
        return (-nb);
    return nb;
}

int my_pow(int nb, int p)
{
    int res = 1;

    if (p == 0)
        return 1;
    if (p < 0)
        return 0;
    for (int i = 0; i < p; i++)
        res *= nb;
    return res;
}

int my_sqrt(int nb)
{
    int i = 0;

    while (i * i < nb)
        i++;
    return i;
}
