/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/utils.h"

sfTime get_elapsed_time(sfClock *clock)
{
    sfTime time = sfClock_getElapsedTime(clock);
    sfClock_restart(clock);
    return time;
}

double get_delta_seconds(sfTime time)
{
    return (sfTime_asSeconds(time));
}