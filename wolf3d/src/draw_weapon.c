/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"

void draw_weapon(wolf_t *wolf, int is_attack)
{
    static sfTexture *tex = NULL;
    static sfSprite *spr = NULL;
    static int loaded = 0;

    if (!loaded) {
        tex = sfTexture_createFromFile("assets/ak47.png", NULL);
        spr = sfSprite_create();
        if (tex && spr)
            sfSprite_setTexture(spr, tex, sfTrue);
        loaded = 1;
    }
    if (!tex || !spr)
        return;

    sfVector2u size = sfTexture_getSize(tex);
    float scale = ((float)WIN_WIDTH * 0.6f) / size.x;
    sfSprite_setScale(spr, (sfVector2f){scale, scale});

    float x = WIN_WIDTH - size.x * scale - 40;
    float y = WIN_HEIGHT - size.y * scale + 20;
    if (is_attack)
        y += 24 * scale;

    sfSprite_setPosition(spr, (sfVector2f){x, y});
    sfRenderWindow_drawSprite(wolf->win, spr, NULL);
}
