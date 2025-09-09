/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

void strip_comments(char *line)
{
    if (line[0] == '#' && line[1] == '#')
        return;
    for (int i = 0; line[i]; i++) {
        if (line[i] == '#') {
            line[i] = '\0';
            break;
        }
    }
}

bool is_comment_line(char *line)
{
    if (line[0] == '\n' || line[0] == '\0')
        return true;
    if (line[0] == '#' && line[1] == '#')
        return false;
    if (line[0] == '#')
        return true;
    strip_comments(line);
    return false;
}

int check_args_count(int argc, char **argv)
{
    for (int i = 1; i < argc; i++) {
        if (!is_digit_string(argv[i])) {
            write(2, "Error\n", 6);
            return 84;
        }
    }
    return 0;
}
