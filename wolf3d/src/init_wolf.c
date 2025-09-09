/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "wolf3d.h"
#include <stdlib.h>
#include <SFML/Audio.h>

static void find_player_start(wolf_t *wolf)
{
    for (int y = 0; y < wolf->map->height; y++) {
        for (int x = 0; wolf->map->tiles[y][x]; x++) {
            if (wolf->map->tiles[y][x] == 'P') {
                wolf->player.x = x + 0.5;
                wolf->player.y = y + 0.5;
                wolf->map->tiles[y][x] = '0';
                return;
            }
        }
    }
    wolf->player.x = 1.5;
    wolf->player.y = 1.5;
}

wolf_t *init_wolf(const char *map_path)
{
    wolf_t *wolf = malloc(sizeof(wolf_t));
    if (!wolf)
        return NULL;
    wolf->map = load_map(map_path);
    if (!wolf->map) {
        free(wolf);
        return NULL;
    }
    wolf->win = sfRenderWindow_create((sfVideoMode){WIN_WIDTH, WIN_HEIGHT, 32},
        "Wolf3D", sfClose | sfResize, NULL);
    if (!wolf->win) {
        destroy_wolf(wolf);
        return NULL;
    }
    find_player_start(wolf);
    wolf->player.dir_x = -1;
    wolf->player.dir_y = 0;
    wolf->player.plane_x = 0;
    wolf->player.plane_y = 0.66;
    wolf->medkit.x = wolf->player.x + 2.0f;
    wolf->medkit.y = wolf->player.y;
    wolf->medkit.picked = 0;
    wolf->medkit_spawn_timer = 0.5f;
    wolf->particles_active = 0;
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        wolf->particles[i].x = 0;
        wolf->particles[i].y = 0;
        wolf->particles[i].dx = 0;
        wolf->particles[i].dy = 0;
        wolf->particles[i].life = 0;
    }
    wolf->hud_msg[0] = '\0';
    wolf->hud_msg_timer = 0.0f;
    wolf->attack = 0;
    wolf->attack_timer = 0.0f;
    wolf->light_on = 0;
    wolf->gun_buffer = sfSoundBuffer_createFromFile("assets/gunshot.wav");
    if (!wolf->gun_buffer)
        return NULL;
    wolf->gun_sound = sfSound_create();
    sfSound_setBuffer(wolf->gun_sound, wolf->gun_buffer);
    wolf->wall_tex = sfTexture_createFromFile("assets/textures/wall.png", NULL);
    wolf->floor_tex = sfTexture_createFromFile("assets/textures/floor.png", NULL);
    wolf->sky_tex = sfTexture_createFromFile("assets/textures/sky.png", NULL);
    if (!wolf->wall_tex || !wolf->floor_tex || !wolf->sky_tex)
        return NULL;
    wolf->sky_sprite = sfSprite_create();
    wolf->floor_sprite = sfSprite_create();
    if (!wolf->sky_sprite || !wolf->floor_sprite)
        return NULL;

    sfVector2u sky_size = sfTexture_getSize(wolf->sky_tex);
    sfVector2u floor_size = sfTexture_getSize(wolf->floor_tex);

    sfSprite_setTexture(wolf->sky_sprite, wolf->sky_tex, sfTrue);
    sfSprite_setScale(wolf->sky_sprite, (sfVector2f){
        (float)WIN_WIDTH / sky_size.x,
        (float)(WIN_HEIGHT / 2) / sky_size.y
    });
    sfSprite_setPosition(wolf->sky_sprite, (sfVector2f){0, 0});

    sfSprite_setTexture(wolf->floor_sprite, wolf->floor_tex, sfTrue);
    sfSprite_setScale(wolf->floor_sprite, (sfVector2f){
        (float)WIN_WIDTH / floor_size.x,
        (float)(WIN_HEIGHT / 2) / floor_size.y
    });
    
    wolf->music = sfMusic_createFromFile("assets/music.ogg");
    if (!wolf->music)
        return NULL;
    sfMusic_setLoop(wolf->music, sfTrue);
    sfMusic_setVolume(wolf->music, 25);
    sfMusic_play(wolf->music);

    sfSprite_setPosition(wolf->floor_sprite, (sfVector2f){0, WIN_HEIGHT / 2});

    return wolf;
}

void destroy_wolf(wolf_t *wolf)
{
    if (!wolf)
        return;

    if (wolf->gun_sound)
        sfSound_destroy(wolf->gun_sound);
    if (wolf->gun_buffer)
        sfSoundBuffer_destroy(wolf->gun_buffer);
    if (wolf->music)
        sfMusic_destroy(wolf->music);
    

    if (wolf->sky_sprite)
        sfSprite_destroy(wolf->sky_sprite);
    if (wolf->floor_sprite)
        sfSprite_destroy(wolf->floor_sprite);
    if (wolf->sky_tex)
        sfTexture_destroy(wolf->sky_tex);
    if (wolf->floor_tex)
        sfTexture_destroy(wolf->floor_tex);
    if (wolf->wall_tex)
        sfTexture_destroy(wolf->wall_tex);

    if (wolf->win)
        sfRenderWindow_destroy(wolf->win);

    if (wolf->map) {
        for (int i = 0; i < wolf->map->height; i++)
            free(wolf->map->tiles[i]);
        free(wolf->map->tiles);
        free(wolf->map);
    }

    free(wolf);
}

void recreate_window(wolf_t *wolf, int fullscreen)
{
    sfVideoMode mode = {WIN_WIDTH, WIN_HEIGHT, 32};
    sfUint32 style = fullscreen ? sfFullscreen : (sfTitlebar | sfClose);
    sfRenderWindow *old = wolf->win;
    wolf->win = sfRenderWindow_create(mode, "Wolf3D", style, NULL);
    sfRenderWindow_destroy(old);
}
