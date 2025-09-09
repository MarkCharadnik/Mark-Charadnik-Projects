/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <math.h>

void draw_sky_and_floor(sfRenderWindow *win, wolf_t *wolf)
{
    sfRenderWindow_drawSprite(win, wolf->sky_sprite, NULL);
    sfRenderWindow_drawSprite(win, wolf->floor_sprite, NULL);
}

void draw_column(ray_t *ray, wolf_t *wolf, int x)
{
    int line_height;
    int draw_start;
    int draw_end;

    if (ray->side == 0)
        ray->dist = (ray->map_x - wolf->player.x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->dist = (ray->map_y - wolf->player.y + (1 - ray->step_y) / 2) / ray->dir_y;

    line_height = (int)(WIN_HEIGHT / ray->dist);
    draw_start = -line_height / 2 + WIN_HEIGHT / 2;
    if (draw_start < 0) draw_start = 0;
    draw_end = line_height / 2 + WIN_HEIGHT / 2;
    if (draw_end >= WIN_HEIGHT) draw_end = WIN_HEIGHT - 1;

    float wall_x = (ray->side == 0)
        ? wolf->player.y + ray->dist * ray->dir_y
        : wolf->player.x + ray->dist * ray->dir_x;
    wall_x -= floor(wall_x);

    int tex_x = (int)(wall_x * sfTexture_getSize(wolf->wall_tex).x);
    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
        tex_x = sfTexture_getSize(wolf->wall_tex).x - tex_x - 1;

    int tex_h = sfTexture_getSize(wolf->wall_tex).y;

    sfColor brightness_color = sfWhite;
    if (wolf->light_on) {
        float brightness = 1.0f - (ray->dist / 10.0f);
        if (brightness < 0.2f)
            brightness = 0.2f;
        brightness_color.r = 255 * brightness;
        brightness_color.g = 255 * brightness;
        brightness_color.b = 255 * brightness;
    }

    sfVertex quad[4] = {
        {{x, draw_start}, brightness_color, {tex_x, 0}},
        {{x + 1, draw_start}, brightness_color, {tex_x + 1, 0}},
        {{x + 1, draw_end}, brightness_color, {tex_x + 1, tex_h}},
        {{x, draw_end}, brightness_color, {tex_x, tex_h}}
    };

    sfRenderStates state = {
        .shader = NULL,
        .texture = wolf->wall_tex,
        .blendMode = sfBlendAlpha,
        .transform = sfTransform_Identity
    };

    sfRenderWindow_drawPrimitives(wolf->win, quad, 4, sfQuads, &state);

    sfVertex top[2] = {
        {{x, 0}, sfColor_fromRGB(10, 10, 10), {0, 0}},
        {{x, draw_start}, sfColor_fromRGB(10, 10, 10), {0, 0}}
    };
    sfRenderWindow_drawPrimitives(wolf->win, top, 2, sfLines, NULL);

    sfVertex bottom[2] = {
        {{x, draw_end}, sfColor_fromRGB(30, 30, 30), {0, 0}},
        {{x, WIN_HEIGHT}, sfColor_fromRGB(30, 30, 30), {0, 0}}
    };
    sfRenderWindow_drawPrimitives(wolf->win, bottom, 2, sfLines, NULL);
}
