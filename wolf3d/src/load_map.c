/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int count_lines(const char *filename)
{
    FILE *file = fopen(filename, "r");
    int count = 0;
    char c;

    if (!file)
        return -1;
    while ((c = fgetc(file)) != EOF)
        if (c == '\n')
            count++;
    fclose(file);
    return count;
}

map_t *load_map(const char *filename)
{
    FILE *file = fopen(filename, "r");
    map_t *map = malloc(sizeof(map_t));
    char buffer[1024];
    int y = 0;

    if (!file || !map)
        return NULL;
    map->height = count_lines(filename);
    map->tiles = malloc(sizeof(char *) * (map->height + 1));
    if (!map->tiles)
        return NULL;
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        map->tiles[y] = strdup(buffer);
        y++;
    }
    map->tiles[y] = NULL;
    fclose(file);
    map->width = (map->tiles[0]) ? strlen(map->tiles[0]) : 0;
    return map;
}
