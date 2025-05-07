/*
** EPITECH PROJECT, 2025
** B-PSU-200-LIL-2-1-minishell2-etienne.pouille
** File description:
** my_is_alphanum
*/

int my_is_alphanum(char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;
    while (str[i] != '\0') {
        if (!((str[i] >= '0' && str[i] <= '9') ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z') ||
            str[i] == '_')) {
            return 0;
        }
        i++;
    }
    return 1;
}
