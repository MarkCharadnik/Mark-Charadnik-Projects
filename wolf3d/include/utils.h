/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/


#ifndef UTILS_H
#define UTILS_H

#include <SFML/System.h>

int error_exit(const char *msg);
int my_strlen(const char *str);
sfTime get_elapsed_time(sfClock *clock);
double get_delta_seconds(sfTime time);

#endif
