/*
** EPITECH PROJECT, 2025
** wolf3D
** File description:
** 
*/

#include "../include/utils.h"
#include <unistd.h>
#include <stdlib.h>

int error_exit(const char *msg)
{
    write(2, msg, my_strlen(msg));
    return (84);
}

int my_strlen(const char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return (i);
}
