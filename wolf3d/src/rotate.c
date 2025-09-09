/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/wolf3d.h"
#include <math.h>

void rotate_left(player_t *p)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
    p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);
    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
    p->plane_y = old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
}

void rotate_right(player_t *p)
{
    double old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
    p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);
    double old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
    p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
}
