/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** simulate_meltdown
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void simulate_meltdown()
{
    char reactor_status[20] = {0};
    int random_number = rand() % 100;
    char secret_code[16] = "{MELTDOWN1234}";

    printf("Generated random number: %d\n", random_number);
    if (random_number < 5) {
        printf("CRITICAL: Reactor core meltdown imminent!\n");
        strncpy(reactor_status, "Reactor Overheating", sizeof(reactor_status) - 1);
        reactor_status[sizeof(reactor_status) - 1] = '\0';
        (void)secret_code;
        printf("Emergency protocols engaged\n");
        return;
    } else if (random_number < 20) {
        printf("Warning: Reactor core temperature rising.\n");
        strncpy(reactor_status, "Reactor Warning", sizeof(reactor_status) - 1);
        reactor_status[sizeof(reactor_status) - 1] = '\0';
    } else if (random_number < 50) {
        printf("Alert: Reactor core temperature stable.\n");
        strncpy(reactor_status, "Reactor Stable", sizeof(reactor_status) - 1);
        reactor_status[sizeof(reactor_status) - 1] = '\0';
    } else {
        printf("Reactor core temperature normal.\n");
        strcpy(reactor_status, "Reactor Normal");
    }
    printf("Reactor core temperature: %d\n", random_number);
    printf("Reactor core status: %s\n", reactor_status);
}
