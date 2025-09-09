/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

void output_robot_count(char *count)
{
    write(1, "#number_of_robots\n", 18);
    write(1, count, my_strlen(count));
    write(1, "\n", 1);
}

static void write_line(const char *line)
{
    if (line[0] != '\0' && line[0] != '\n') {
        write(1, line, my_strlen(line));
        if (line[my_strlen(line) - 1] != '\n')
            write(1, "\n", 1);
    }
}

void display_rooms(maze_data_t *data)
{
    write(1, "#rooms\n", 7);
    for (int i = 1; data->lines[i]; i++) {
        if (is_tunnel_format(data->lines[i]))
            continue;
        write_line(data->lines[i]);
    }
}

void display_tunnels(maze_data_t *data)
{
    int header_printed = 0;

    for (int i = 1; data->lines[i]; i++) {
        if (!is_tunnel_format(data->lines[i]))
            continue;
        if (!header_printed) {
            write(1, "#tunnels\n", 9);
            header_printed = 1;
        }
        write_line(data->lines[i]);
    }
}

void output_data(maze_data_t *data)
{
    output_robot_count(data->lines[0]);
    display_rooms(data);
    display_tunnels(data);
}
