/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"

void handle_events(wolf_t *wolf)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(wolf->win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(wolf->win);

        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEscape)
                sfRenderWindow_close(wolf->win);
            if (event.key.code == sfKeyF)
                wolf->light_on = !wolf->light_on;
            if (event.key.code == sfKeyK)
                save_player(wolf);
            if (event.key.code == sfKeyL)
                load_player(wolf);
            if (event.key.code == sfKeySpace && wolf->attack == 0) {
                wolf->attack = 1;
                wolf->attack_timer = 0.15f;
                if (wolf->gun_sound)
                    sfSound_play(wolf->gun_sound);
            }
            if (event.key.code == sfKeyH)
                wolf->show_help = !wolf->show_help;
        }
    }
    if (sfKeyboard_isKeyPressed(sfKeyW))
        move_forward(&wolf->player, wolf->map);
    if (sfKeyboard_isKeyPressed(sfKeyS))
        move_backward(&wolf->player, wolf->map);
    if (sfKeyboard_isKeyPressed(sfKeyA))
        strafe_left(&wolf->player, wolf->map);
    if (sfKeyboard_isKeyPressed(sfKeyD))
        strafe_right(&wolf->player, wolf->map);
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        rotate_left(&wolf->player);
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        rotate_right(&wolf->player);
}
