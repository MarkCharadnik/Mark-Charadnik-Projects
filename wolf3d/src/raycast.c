/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/wolf3d.h"
#include <math.h>

static void calculate_ray(ray_t *ray, player_t *p, int x, int w)
{
    double cam_x = 2 * x / (double)w - 1;

    ray->dir_x = p->dir_x + p->plane_x * cam_x;
    ray->dir_y = p->dir_y + p->plane_y * cam_x;
    ray->map_x = (int)p->x;
    ray->map_y = (int)p->y;
    ray->delta_x = fabs(1 / ray->dir_x);
    ray->delta_y = fabs(1 / ray->dir_y);
}

static void set_step(ray_t *ray, player_t *p)
{
    if (ray->dir_x < 0) {
        ray->step_x = -1;
        ray->side_dist_x = (p->x - ray->map_x) * ray->delta_x;
    } else {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - p->x) * ray->delta_x;
    }
    if (ray->dir_y < 0) {
        ray->step_y = -1;
        ray->side_dist_y = (p->y - ray->map_y) * ray->delta_y;
    } else {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - p->y) * ray->delta_y;
    }
}

static void perform_dda(ray_t *ray, map_t *map)
{
    while (!ray->hit) {
        if (ray->side_dist_x < ray->side_dist_y) {
            ray->side_dist_x += ray->delta_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        } else {
            ray->side_dist_y += ray->delta_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (map->tiles[ray->map_y][ray->map_x] == '1')
            ray->hit = 1;
    }
}

void render_scene(wolf_t *wolf)
{
    int x = 0;

    while (x < WIN_WIDTH) {
        ray_t ray = {0};
        calculate_ray(&ray, &wolf->player, x, WIN_WIDTH);
        set_step(&ray, &wolf->player);
        perform_dda(&ray, wolf->map);
        draw_column(&ray, wolf, x);
        x++;
    }
}
