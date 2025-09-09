/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** monitor_radiation_levels
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void monitor_radiation_levels()
{
    char buffer[256] = {0};
	long level;

    printf("Enter radiation levels: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        printf("Error reading input\n");
        return;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    printf("Radiation Levels: %s\n", buffer);
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] < '0' || buffer[i] > '9') {
            printf("Invalid input: Only numeric values are allowed\n");
            return;
        }
    }
    level = strtol(buffer, NULL, 10);
    if (level > 1000) {
        printf("WARNING: Critical radiation levels detected!\n");
    } else if (level > 500) {
        printf("WARNING: High radiation levels detected!\n");
    } else {
        printf("Radiation levels within acceptable range.\n");
    }
}
