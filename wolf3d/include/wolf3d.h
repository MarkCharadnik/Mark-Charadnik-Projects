/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#ifndef WOLF3D_H
#define WOLF3D_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include "map.h"
#include "render.h"
#include "input.h"
#include "utils.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MOVE_SPEED 0.10
#define ROT_SPEED 0.05
#define HUD_MSG_LEN 32
#define PARTICLE_COUNT 24
#define TILE_SIZE 32

typedef struct {
    float x, y;
    int picked;
} medkit_t;

typedef struct {
    float x, y;
    float dx, dy;
    float life;
} particle_t;

typedef struct player_s {
    double x, y;
    double dir_x, dir_y;
    double plane_x, plane_y;
    int hp;
} player_t;

typedef struct wolf_s {
    sfRenderWindow *win;
    map_t *map;
    player_t player;
    int light_on;
    char hud_msg[HUD_MSG_LEN];
    float hud_msg_timer;
    int attack;
    float attack_timer;
    medkit_t medkit;
    sfMusic *music;
    int medkit_picked;
    particle_t particles[PARTICLE_COUNT];
    int particles_active;
    int show_help;
    sfSound *gun_sound;
    sfSoundBuffer *gun_buffer;
    sfTexture *wall_tex;
    sfTexture *floor_tex;
    sfTexture *sky_tex;
    sfSprite *sky_sprite;
    sfSprite *floor_sprite;
    float medkit_spawn_timer;

} wolf_t;

void draw_hud(wolf_t *wolf);
void game_loop(wolf_t *wolf);
wolf_t *init_wolf(const char *map_path);
void destroy_wolf(wolf_t *wolf);
int show_main_menu(wolf_t *wolf);
void show_settings(wolf_t *wolf);
void recreate_window(wolf_t *wolf, int fullscreen);
void save_player(wolf_t *wolf);
void load_player(wolf_t *wolf);
void draw_weapon(wolf_t *wolf, int is_attack);
void spawn_particles(wolf_t *wolf, float x, float y);
void draw_medkit(wolf_t *wolf);
void update_particles(wolf_t *wolf, float dt);
void draw_particles(wolf_t *wolf);
void draw_minimap(wolf_t *wolf);
void draw_sky_and_floor(sfRenderWindow *win, wolf_t *wolf);


#endif