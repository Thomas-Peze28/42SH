/*
** EPITECH PROJECT, 2024
** minishell1
** File description:
** minishell1
*/
#include "workspace.h"
#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ncurses.h>

static void print_ascii_ncurses(const char *line, int *color_pairs)
{
    int start = 0;
    int end = 0;
    int col = 0;

    for (col = 0; col < 4; col++) {
        end = start + 22;
        attron(COLOR_PAIR(color_pairs[col]));
        printw("%.*s", 22, line + start);
        attroff(COLOR_PAIR(color_pairs[col]));
        start = end;
    }
    printw("\n");
}

static void print_ascii_ansi(const char *line, const char **ansi_colors)
{
    int start = 0;
    int end = 0;
    int col = 0;

    for (col = 0; col < 4; col++) {
        end = start + 22;
        write(1, ansi_colors[col], strlen(ansi_colors[col]));
        write(1, line + start, 22);
        write(1, "\033[0m", 4);
        start = end;
    }
    write(1, "\n", 1);
}

static void print_ascii_art(const char **ascii, int lines)
{
    int i = 0;
    int color_pairs[4] = {1, 2, 3, 4};
    const char *ansi_colors[4] = {"\033[36m",
        "\033[35m", "\033[33m", "\033[32m"};

    for (i = 0; i < lines; i++) {
        if (!(!isatty(0) || !isatty(1)))
            print_ascii_ncurses(ascii[i], color_pairs);
        else
            print_ascii_ansi(ascii[i], ansi_colors);
    }
    if (!(!isatty(0) || !isatty(1)))
        refresh();
}

int print_42sh_ascii(void)
{
    static const char *ascii[] = {
        "                    .-')   ('-. .-.",
        "                   ( OO ).( OO )  /",
        "    .---.  .-----.(_)---\\_,--. ,--.",
        "   / .  | / ,-.   /    _ ||  | |  |",
        "  / /|  | '-'  |  \\  :` `.|   .|  |",
        " / / |  |_   .'  / '..`''.|       |",
        "/  '-'    |.'  /__.-._)   |  .-.  |",
        "`----|  |-|       \\       |  | |  |",
        "     `--' `-------'`-----'`--' `--'"
    };
    int lines = sizeof(ascii) / sizeof(ascii[0]);

    print_ascii_art(ascii, lines);
    return 0;
}
