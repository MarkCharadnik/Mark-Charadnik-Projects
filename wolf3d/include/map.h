/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#ifndef MAP_H
#define MAP_H

typedef struct map_s {
    char **tiles;
    int width;
    int height;
} map_t;

map_t *load_map(const char *filename);
char **append_line(char **map, char *line);
char **append_line(char **map, char *line);

#endif
