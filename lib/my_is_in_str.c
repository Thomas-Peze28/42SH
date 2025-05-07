/*
** EPITECH PROJECT, 2025
** base_folder
** File description:
** is_in_str
*/

int my_is_in_str(char c, char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (c == str[i]) {
            return 1;
        }
        i++;
    }
    return 0;
}
