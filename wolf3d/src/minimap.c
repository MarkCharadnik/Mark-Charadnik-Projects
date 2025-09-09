#include "wolf3d.h"
#include <SFML/Graphics.h>

#define MM_SIZE 160
#define MM_MARGIN 12

void draw_minimap(wolf_t *wolf)
{
    int tile_w = MM_SIZE / wolf->map->width;
    int tile_h = MM_SIZE / wolf->map->height;

    for (int y = 0; y < wolf->map->height; y++) {
        for (int x = 0; x < wolf->map->width; x++) {
            sfRectangleShape *tile = sfRectangleShape_create();
            sfRectangleShape_setSize(tile, (sfVector2f){tile_w - 1, tile_h - 1});
            sfRectangleShape_setPosition(tile, (sfVector2f){
                MM_MARGIN + x * tile_w, MM_MARGIN + y * tile_h
            });
            char cell = wolf->map->tiles[y][x];
            if (cell == '1')
                sfRectangleShape_setFillColor(tile, sfColor_fromRGB(55, 55, 55));
            else
                sfRectangleShape_setFillColor(tile, sfColor_fromRGB(170, 170, 170));
            sfRenderWindow_drawRectangleShape(wolf->win, tile, NULL);
            sfRectangleShape_destroy(tile);
        }
    }
    if (!wolf->medkit_picked) {
        sfCircleShape *med = sfCircleShape_create();
        sfCircleShape_setRadius(med, tile_w * 0.32f);
        sfCircleShape_setFillColor(med, sfColor_fromRGB(250, 40, 40));
        sfCircleShape_setPosition(med, (sfVector2f){
            MM_MARGIN + wolf->medkit.x * tile_w - tile_w * 0.16f,
            MM_MARGIN + wolf->medkit.y * tile_h - tile_h * 0.16f
        });
        sfRenderWindow_drawCircleShape(wolf->win, med, NULL);
        sfCircleShape_destroy(med);
    }
    sfCircleShape *player = sfCircleShape_create();
    sfCircleShape_setRadius(player, tile_w * 0.28f);
    sfCircleShape_setFillColor(player, sfColor_fromRGB(20, 190, 20));
    sfCircleShape_setPosition(player, (sfVector2f){
        MM_MARGIN + wolf->player.x * tile_w - tile_w * 0.14f,
        MM_MARGIN + wolf->player.y * tile_h - tile_h * 0.14f
    });
    sfRenderWindow_drawCircleShape(wolf->win, player, NULL);
    sfCircleShape_destroy(player);
    sfVertex line[] = {
        {
            {MM_MARGIN + wolf->player.x * tile_w + tile_w * 0.01f,
             MM_MARGIN + wolf->player.y * tile_h + tile_h * 0.01f},
            sfColor_fromRGB(40, 250, 40),
            {0, 0}
        },
        {
            {MM_MARGIN + (wolf->player.x + wolf->player.dir_x * 0.7f) * tile_w,
             MM_MARGIN + (wolf->player.y + wolf->player.dir_y * 0.7f) * tile_h},
            sfColor_fromRGB(40, 250, 40),
            {0, 0}
        }
    };
    sfRenderWindow_drawPrimitives(wolf->win, line, 2, sfLines, NULL);
}
