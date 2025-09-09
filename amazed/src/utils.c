/*
** EPITECH PROJECT, 2025
** A-MAZE-D
** File description:
** main.c
*/

#include "amazed.h"

int is_digit_string(const char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int my_strlen(const char *str)
{
    int len;

    len = 0;
    while (str[len] != '\0') {
        len = len + 1;
    }
    return len;
}

char *my_strdup(const char *src)
{
    int len;
    char *copy;
    int i;

    len = my_strlen(src);
    copy = malloc(sizeof(char) * (len + 1));
    if (copy == NULL) {
        return NULL;
    }
    i = 0;
    while (src[i] != '\0') {
        copy[i] = src[i];
        i = i + 1;
    }
    copy[i] = '\0';
    return copy;
}
