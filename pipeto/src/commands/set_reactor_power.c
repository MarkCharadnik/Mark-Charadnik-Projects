/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** set_reactor_power
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


int safe_strtol(const char *str, int *result, int min_val, int max_val)
{
    char *endptr;
    long val;

    if (str == NULL || result == NULL) {
        return -1;
    }
    errno = 0;
    val = strtol(str, &endptr, 10);
    if (endptr == str) {
        return -1;
    }
    if (*endptr != '\0' && *endptr != '\n') {
        return -1;
    }
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
        (val > max_val) || (val < min_val)) {
        return -1;
    }
    *result = (int)val;
    return 0;
}

void set_reactor_power(void)
{
    char input[32] = {0};
    int input_power;
    int POWER_ADJUSTMENT = 1000;
    int MAX_SAFE_POWER = 9000;
    int new_power;
    char confirm[8] = {0};

    printf("Enter reactor power level (0-%d): ", INT_MAX - POWER_ADJUSTMENT);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return;
    }
    input[strcspn(input, "\n")] = '\0';
    if (safe_strtol(input, &input_power, 0, INT_MAX - POWER_ADJUSTMENT) != 0) {
        printf("Error: Invalid power level. Please enter a valid number.\n");
        return;
    }
    if (__builtin_add_overflow(input_power, POWER_ADJUSTMENT, &new_power)) {
        printf("Error: Power level would exceed maximum safe value.\n");
        return;
    }
    if (new_power > MAX_SAFE_POWER) {
        printf("Warning: Power level %d exceeds recommended maximum of %d.\n", 
               new_power, MAX_SAFE_POWER);
        printf("Are you sure you want to continue? (yes/no): ");
        if (fgets(confirm, sizeof(confirm), stdin) == NULL ||
            strncmp(confirm, "yes", 3) != 0) {
            printf("Operation cancelled. Power level not changed.\n");
            return;
        }
    }
    printf("Reactor power set to: %d\n", new_power);
    printf("Reactor operating within safe parameters.\n");
}
