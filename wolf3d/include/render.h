/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/


#ifndef RENDER_H
#define RENDER_H

#include <SFML/Graphics.h>

struct wolf_s;
struct player_s;
struct map_s;

typedef struct ray_s {
    double dir_x, dir_y;
    int map_x, map_y;
    double delta_x, delta_y;
    double side_dist_x, side_dist_y;
    int step_x, step_y;
    int hit, side;
    double dist;
} ray_t;

void render_scene(struct wolf_s *wolf);
void draw_column(ray_t *ray, struct wolf_s *wolf, int x);

#endif
