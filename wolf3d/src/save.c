/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/wolf3d.h"
#include <stdio.h>

void save_game(wolf_t *wolf)
{
    FILE *file = fopen("save.dat", "w");

    if (!file)
        return;
    fprintf(file, "%f %f\n", wolf->player.x, wolf->player.y);
    fclose(file);
}

void load_game(wolf_t *wolf)
{
    FILE *file = fopen("save.dat", "r");

    if (!file)
        return;
    fscanf(file, "%lf %lf", &wolf->player.x, &wolf->player.y);
    fclose(file);
}

void save_player(wolf_t *wolf) {
    FILE *f = fopen("save.txt", "w");
    if (!f) return;
    fprintf(f, "%.6f %.6f %.6f %.6f\n",
            wolf->player.x, wolf->player.y,
            wolf->player.dir_x, wolf->player.dir_y);
    fclose(f);
    snprintf(wolf->hud_msg, HUD_MSG_LEN, "Saved!");
    wolf->hud_msg_timer = 2.0f;
    }

void load_player(wolf_t *wolf) {
    FILE *f = fopen("save.txt", "r");
    if (!f) return;
    fscanf(f, "%lf %lf %lf %lf",
           &wolf->player.x, &wolf->player.y,
           &wolf->player.dir_x, &wolf->player.dir_y);
    fclose(f);
    snprintf(wolf->hud_msg, HUD_MSG_LEN, "Loaded!");
    wolf->hud_msg_timer = 2.0f;
}
