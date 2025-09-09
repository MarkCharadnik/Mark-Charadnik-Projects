/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <math.h>

static int is_wall(map_t *map, double x, double y)
{
    if (x < 0 || y < 0 || y >= map->height || x >= map->width)
        return (1);
    return (map->tiles[(int)y][(int)x] == '1');
}

void move_forward(player_t *p, map_t *map)
{
    double new_x = p->x + p->dir_x * MOVE_SPEED;
    double new_y = p->y + p->dir_y * MOVE_SPEED;

    if (!is_wall(map, new_x, p->y))
        p->x = new_x;
    if (!is_wall(map, p->x, new_y))
        p->y = new_y;
}

void move_backward(player_t *p, map_t *map)
{
    double new_x = p->x - p->dir_x * MOVE_SPEED;
    double new_y = p->y - p->dir_y * MOVE_SPEED;

    if (!is_wall(map, new_x, p->y))
        p->x = new_x;
    if (!is_wall(map, p->x, new_y))
        p->y = new_y;
}

void strafe_left(player_t *p, map_t *map)
{
    double new_x = p->x - p->plane_x * MOVE_SPEED;
    double new_y = p->y - p->plane_y * MOVE_SPEED;

    if (!is_wall(map, new_x, p->y))
        p->x = new_x;
    if (!is_wall(map, p->x, new_y))
        p->y = new_y;
}

void strafe_right(player_t *p, map_t *map)
{
    double new_x = p->x + p->plane_x * MOVE_SPEED;
    double new_y = p->y + p->plane_y * MOVE_SPEED;

    if (!is_wall(map, new_x, p->y))
        p->x = new_x;
    if (!is_wall(map, p->x, new_y))
        p->y = new_y;
}