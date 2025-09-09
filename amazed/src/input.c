/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

char **expand_array(maze_data_t *data, char **array, char *line)
{
    char **new_arr;
    int i;

    new_arr = malloc(sizeof(char *) * (data->length + 1));
    if (new_arr == NULL)
        return NULL;
    i = 0;
    while (i < data->length - 1) {
        new_arr[i] = array[i];
        i++;
    }
    new_arr[data->length - 1] = my_strdup(line);
    new_arr[data->length] = NULL;
    free(array);
    return new_arr;
}

static int process_line(maze_data_t *data, char *line)
{
    char **new_lines;

    if (is_comment_line(line)) {
        return 0;
    }
    data->length = data->length + 1;
    new_lines = expand_array(data, data->lines, line);
    if (new_lines == NULL) {
        return -1;
    }
    data->lines = new_lines;
    return 0;
}

static int handle_read_line(maze_data_t *data, char *line, ssize_t read_len)
{
    if (read_len > 0) {
        if (line[read_len - 1] == '\n') {
            line[read_len - 1] = '\0';
        }
    }
    if (process_line(data, line) == -1) {
        return -1;
    }
    return 0;
}

void read_input_lines(maze_data_t *data)
{
    char *line;
    size_t len;
    ssize_t read_len;
    int status;

    line = NULL;
    len = 0;
    read_len = 0;
    status = 0;
    read_len = getline(&line, &len, stdin);
    while (read_len != -1) {
        status = handle_read_line(data, line, read_len);
        if (status == -1) {
            free(line);
            return;
        }
        read_len = getline(&line, &len, stdin);
    }
    free(line);
}

maze_data_t *read_input(void)
{
    maze_data_t *data;

    data = malloc(sizeof(maze_data_t));
    if (data == NULL)
        return NULL;
    data->length = 0;
    data->lines = NULL;
    read_input_lines(data);
    output_data(data);
    return data;
}
