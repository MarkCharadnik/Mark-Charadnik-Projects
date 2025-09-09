#include "wolf3d.h"
#include <SFML/Window/Keyboard.h>

int show_main_menu(wolf_t *wolf)
{
    sfFont *font = sfFont_createFromFile("assets/font.ttf");
    sfText *text = sfText_create();
    int choice = 0;
    char *labels[3] = {"Start", "Settings", "Exit"};
    sfEvent event;

    if (!font || !text)
        return 1;
    while (sfRenderWindow_isOpen(wolf->win)) {
        while (sfRenderWindow_pollEvent(wolf->win, &event)) {
            if (event.type == sfEvtClosed)
                return 1;
            if (event.type == sfEvtKeyPressed) {
                if (event.key.code == sfKeyDown)
                    choice = (choice + 1) % 3;
                if (event.key.code == sfKeyUp)
                    choice = (choice + 2) % 3;
                if (event.key.code == sfKeyReturn) {
                    if (choice == 0)
                        return 0;
                    if (choice == 1)
                        show_settings(wolf);
                    if (choice == 2)
                        return 1;
                }
            }
        }
        sfRenderWindow_clear(wolf->win, sfBlack);
        for (int i = 0; i < 3; i++) {
            sfText_setString(text, labels[i]);
            sfText_setFont(text, font);
            sfText_setCharacterSize(text, 32);
            sfText_setColor(text, i == choice ? sfYellow : sfWhite);
            sfText_setPosition(text, (sfVector2f){WIN_WIDTH/2 - 60, WIN_HEIGHT/2 + i*40});
            sfRenderWindow_drawText(wolf->win, text, NULL);
        }
        sfRenderWindow_display(wolf->win);
    }
    sfText_destroy(text);
    sfFont_destroy(font);
    return 1;
}
