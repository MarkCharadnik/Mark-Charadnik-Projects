/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include <stdlib.h>
#include <string.h>

char **append_line(char **map, char *line)
{
    int i = 0;
    char **new_map;

    if (map) {
        while (map[i])
            i++;
    }

    new_map = malloc(sizeof(char *) * (i + 2));
    if (!new_map)
        return NULL;

    for (int j = 0; j < i; j++)
        new_map[j] = map[j];

    new_map[i] = strdup(line);
    new_map[i + 1] = NULL;

    free(map);
    return new_map;
}
