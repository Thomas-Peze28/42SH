/*
** EPITECH PROJECT, 2025
** lib
** File description:
** my_isprintable
*/

int my_isprintable(char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!(str[i] >= 32 && str[i] <= 126)) {
            return 0;
        }
        i++;
    }
    return 1;
}
