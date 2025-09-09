#include "wolf3d.h"

void game_loop(wolf_t *wolf)
{
    sfClock *clock = sfClock_create();

    while (sfRenderWindow_isOpen(wolf->win)) {
        handle_events(wolf);
        float dt = sfTime_asSeconds(get_elapsed_time(clock));

        sfRenderWindow_clear(wolf->win, sfBlack);
        draw_sky_and_floor(wolf->win, wolf);
        render_scene(wolf);
        if (wolf->medkit_spawn_timer > 0.0f)
            wolf->medkit_spawn_timer -= dt;
        draw_medkit(wolf);
        update_particles(wolf, dt);
        draw_particles(wolf);
        draw_minimap(wolf);
        draw_hud(wolf);
        sfRenderWindow_display(wolf->win);
        if (wolf->hud_msg_timer > 0.0f) {
            wolf->hud_msg_timer -= dt;
            if (wolf->hud_msg_timer < 0.0f)
                wolf->hud_msg_timer = 0.0f;
        }
        if (wolf->attack_timer > 0.0f) {
            wolf->attack_timer -= dt;
            if (wolf->attack_timer <= 0.0f) {
                wolf->attack_timer = 0.0f;
                wolf->attack = 0;
            }
        }
    }

    sfClock_destroy(clock);
}
