/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <math.h>
#include <stdlib.h>

void spawn_particles(wolf_t *wolf, float x, float y)
{
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        float angle = ((float)rand() / RAND_MAX) * 2 * M_PI;
        float speed = ((float)rand() / RAND_MAX) * 2.5f + 1.0f;
        wolf->particles[i].x = x;
        wolf->particles[i].y = y;
        wolf->particles[i].dx = cosf(angle) * speed * 0.07f;
        wolf->particles[i].dy = sinf(angle) * speed * 0.07f;
        wolf->particles[i].life = 0.5f + ((float)rand() / RAND_MAX) * 0.5f;
    }
    wolf->particles_active = 1;
}