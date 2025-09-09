/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <SFML/Graphics.h>
#include <math.h>
#include <stdio.h>

void draw_medkit(wolf_t *wolf)
{
    if (wolf->medkit.picked)
        return;

    static sfTexture *tex = NULL;
    static sfSprite *spr = NULL;

    if (!tex) tex = sfTexture_createFromFile("assets/medkit.png", NULL);
    if (!spr) spr = sfSprite_create();
    if (!tex || !spr)
        return;
    sfSprite_setTexture(spr, tex, sfTrue);

    float medkit_x = wolf->medkit.x;
    float medkit_y = wolf->medkit.y;

    float dx = medkit_x - wolf->player.x;
    float dy = medkit_y - wolf->player.y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist < 0.6f) {
        wolf->medkit.picked = 1;
        wolf->player.hp += 30;
        if (wolf->player.hp > 100) wolf->player.hp = 100;
        snprintf(wolf->hud_msg, HUD_MSG_LEN, "Picked up medkit!");
        wolf->hud_msg_timer = 2.0f;
        spawn_particles(wolf, medkit_x, medkit_y);
        return;
    }

    float rel_x = medkit_x - wolf->player.x;
    float rel_y = medkit_y - wolf->player.y;
    float invDet = 1.0f / (wolf->player.plane_x * wolf->player.dir_y - wolf->player.dir_x * wolf->player.plane_y);
    float transformX = invDet * (wolf->player.dir_y * rel_x - wolf->player.dir_x * rel_y);
    float transformY = invDet * (-wolf->player.plane_y * rel_x + wolf->player.plane_x * rel_y);

    if (transformY <= 0)
        return;

    int screenX = (int)((WIN_WIDTH / 2) * (1 + transformX / transformY));
    int spriteHeight = fabs(WIN_HEIGHT / transformY / 2.2f);
    int spriteWidth = spriteHeight;

    int drawStartY = -spriteHeight / 2 + WIN_HEIGHT - spriteHeight / 6;
    if (drawStartY < 0) drawStartY = 0;
    int drawEndY = drawStartY + spriteHeight;
    if (drawEndY > WIN_HEIGHT) drawEndY = WIN_HEIGHT;
    int drawStartX = -spriteWidth / 2 + screenX;
    if (drawStartX < 0) drawStartX = 0;
    int drawEndX = drawStartX + spriteWidth;
    if (drawEndX > WIN_WIDTH) drawEndX = WIN_WIDTH;

    sfSprite_setScale(spr, (sfVector2f){
        spriteWidth / (float)sfTexture_getSize(tex).x,
        spriteHeight / (float)sfTexture_getSize(tex).y
    });
    sfSprite_setPosition(spr, (sfVector2f){drawStartX, drawStartY});

    sfRenderWindow_drawSprite(wolf->win, spr, NULL);
}
