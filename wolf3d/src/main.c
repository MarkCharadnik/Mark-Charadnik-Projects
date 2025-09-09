/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/wolf3d.h"
#include <unistd.h>

int main(int ac, char **av)
{
    if (ac < 2) {
        write(2, "Usage: ./wolf3d [map_file]\n", 28);
        return 84;
    }
    wolf_t *wolf = init_wolf(av[1]);
    if (!wolf)
        return 84;
    int menu_choice = show_main_menu(wolf);
    if (menu_choice == 0)
        game_loop(wolf);
    destroy_wolf(wolf);
    return 0;
}
