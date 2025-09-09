/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <SFML/Window/Keyboard.h>
#include <stdio.h>

void show_settings(wolf_t *wolf)
{
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfText *text = sfText_create();
    int setting = 0;
    int volume = 5;
    int fullscreen = 0;
    sfEvent event;
    char buf[64];

    if (!font || !text)
        return;
    while (sfRenderWindow_isOpen(wolf->win)) {
        while (sfRenderWindow_pollEvent(wolf->win, &event)) {
            if (event.type == sfEvtClosed)
                return;
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyEscape)
                    return;
                if (event.key.code == sfKeyUp)
                    setting = (setting + 1) % 2;
                if (event.key.code == sfKeyDown)
                    setting = (setting + 1) % 2;
                if (event.key.code == sfKeyLeft) {
                    if (setting == 0 && volume > 0)
                        volume--;
                    if (setting == 1 && fullscreen != 0) {
                        fullscreen = 0;
                        recreate_window(wolf, fullscreen);
                    }
                }
                if (event.key.code == sfKeyRight) {
                    if (setting == 0 && volume < 10)
                        volume++;
                    if (setting == 1 && fullscreen != 1) {
                        fullscreen = 1;
                        recreate_window(wolf, fullscreen);
                    }
                }
            }
        }
        sfRenderWindow_clear(wolf->win, sfBlack);
        snprintf(buf, sizeof(buf), "Volume: [%d]", volume);
        sfText_setFont(text, font);
        sfText_setCharacterSize(text, 28);
        sfText_setString(text, buf);
        sfText_setColor(text, setting == 0 ? sfYellow : sfWhite);
        sfText_setPosition(text, (sfVector2f){WIN_WIDTH/2 - 100, WIN_HEIGHT/2});
        sfRenderWindow_drawText(wolf->win, text, NULL);
        snprintf(buf, sizeof(buf), "Mode: [%s]", fullscreen ? "Fullscreen" : "Windowed");
        sfText_setString(text, buf);
        sfText_setColor(text, setting == 1 ? sfYellow : sfWhite);
        sfText_setPosition(text, (sfVector2f){WIN_WIDTH/2 - 100, WIN_HEIGHT/2 + 40});
        sfRenderWindow_drawText(wolf->win, text, NULL);
        sfRenderWindow_display(wolf->win);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
}
