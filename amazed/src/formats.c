/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int char_to_num(char c)
{
    if (is_digit(c))
        return c - '0';
    return -1;
}

int is_room_format(char *str)
{
    int spaces;
    int i;

    spaces = 0;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            spaces = spaces + 1;
        }
        i = i + 1;
    }
    if (spaces == 2) {
        return 1;
    }
    return 0;
}

int is_tunnel_format(const char *str)
{
    int dashes;
    int i;

    dashes = 0;
    i = 0;
    while (str[i] != '\0') {
        if (str[i] == '-') {
            dashes = dashes + 1;
        }
        i = i + 1;
    }
    if (dashes == 1) {
        return 1;
    }
    return 0;
}

int count_rooms_in_array(char **arr)
{
    int count = 0;

    for (int i = 0; arr[i]; i++)
        if (is_room_format(arr[i]))
            count++;
    return count;
}
