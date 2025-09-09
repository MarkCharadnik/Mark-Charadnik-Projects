/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"
#include <stdio.h>

int parse_tunnel_verts(const char *line, int *src, int *dest)
{
    int i = 0;
    int dash_index = -1;

    while (line[i] != '\0') {
        if (line[i] == '-') {
            dash_index = i;
            break;
        }
        i = i + 1;
    }
    if (dash_index == -1)
        return 0;
    *src = my_getnbr_range(line, 0, dash_index);
    *dest = my_getnbr_range(line, dash_index + 1, -1);
    return 1;
}

int my_getnbr_range(const char *str, int start, int end)
{
    int result = 0;
    int i = start;

    if (end == -1)
        end = my_strlen(str);
    while (i < end && str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i = i + 1;
    }
    return result;
}

static void update_max_if_needed(int *max, int value)
{
    if (value > *max)
        *max = value;
}

static void process_line_for_max(const char *line, int *max)
{
    int src;
    int dest;
    int parsed;

    if (is_tunnel_format(line) == 1) {
        parsed = parse_tunnel_verts(line, &src, &dest);
        if (parsed == 1) {
            update_max_if_needed(max, src);
            update_max_if_needed(max, dest);
        }
    }
}

int get_max_vertex(char **arr)
{
    int max;
    int i;

    max = -1;
    i = 0;
    while (arr[i] != NULL) {
        process_line_for_max(arr[i], &max);
        i = i + 1;
    }
    return max;
}
