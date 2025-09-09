/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <stdio.h>

void draw_hud(wolf_t *wolf)
{
    static sfFont *font = NULL;
    static sfText *text_main = NULL;
    static sfText *text_msg = NULL;
    if (!font) font = sfFont_createFromFile("assets/font.ttf");
    if (!text_main) text_main = sfText_create();
    if (!text_msg) text_msg = sfText_create();
    if (!font || !text_main || !text_msg)
        return;

    char buffer[128];

    sfText_setFont(text_main, font);
    sfText_setCharacterSize(text_main, 18);
    sfText_setColor(text_main, sfWhite);
    sfText_setPosition(text_main, (sfVector2f){10, 10});

    snprintf(buffer, sizeof(buffer),
        "X: %.2f\nY: %.2f\nDirX: %.2f\nDirY: %.2f",
        wolf->player.x, wolf->player.y,
        wolf->player.dir_x, wolf->player.dir_y);

    sfText_setString(text_main, buffer);
    sfRenderWindow_drawText(wolf->win, text_main, NULL);

    if (wolf->hud_msg_timer > 0.0f && wolf->hud_msg[0]) {
        sfText_setFont(text_msg, font);
        sfText_setCharacterSize(text_msg, 18);
        sfText_setColor(text_msg, sfGreen);
        sfText_setPosition(text_msg, (sfVector2f){10, 80});
        sfText_setString(text_msg, wolf->hud_msg);
        sfRenderWindow_drawText(wolf->win, text_msg, NULL);
    }

    draw_weapon(wolf, wolf->attack);
    
    if (wolf->show_help) {
        sfText *help = sfText_create();
        sfFont *font = sfFont_createFromFile("assets/font.ttf");
        sfText_setFont(help, font);
        sfText_setCharacterSize(help, 18);
        sfText_setFillColor(help, sfColor_fromRGB(250, 250, 240));
        sfText_setPosition(help, (sfVector2f){64, 64});
        sfText_setString(help,
            "WASD: Move\n"
            "Arrows: Turn\n"
            "F: Flashlight\n"
            "Space: Attack\n"
            "K/L: Save/Load\n"
            "ESC: Quit\n"
            "H: Toggle Help\n"
        );
        sfRenderWindow_drawText(wolf->win, help, NULL);
        sfText_destroy(help);
        sfFont_destroy(font);
    }
}
