/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_strlen
*/

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return i;
}

int my_tablen(char **tab)
{
    int i = 0;

    for (i = 0; tab[i] != 0; i++);
    return i;
}
