/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <SFML/Graphics.h>
#ifndef TILE_SIZE
#define TILE_SIZE 32
#endif

void update_particles(wolf_t *wolf, float dt)
{
    if (!wolf->particles_active)
        return;

    int alive = 0;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (wolf->particles[i].life > 0.0f) {
            wolf->particles[i].x += wolf->particles[i].dx;
            wolf->particles[i].y += wolf->particles[i].dy;
            wolf->particles[i].life -= dt;
            if (wolf->particles[i].life > 0.0f)
                alive = 1;
        }
    }
    wolf->particles_active = alive;
}

void draw_particles(wolf_t *wolf)
{
    if (!wolf->particles_active)
        return;

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (wolf->particles[i].life > 0.0f) {
            sfCircleShape *shape = sfCircleShape_create();
            sfCircleShape_setRadius(shape, 5.0f);
            sfCircleShape_setFillColor(shape, sfColor_fromRGBA(255, 70, 70, 200));
            sfCircleShape_setPosition(shape, (sfVector2f){
                wolf->particles[i].x * TILE_SIZE - 5,
                wolf->particles[i].y * TILE_SIZE - 5
            });
            sfRenderWindow_drawCircleShape(wolf->win, shape, NULL);
            sfCircleShape_destroy(shape);
        }
    }
}
