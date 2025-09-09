/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** run_diagnostic
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void run_diagnostic(void)
{
    char input[32] = {0};

    printf("Enter diagnostic mode (normal/advanced): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input\n");
        return;
    }
    input[strcspn(input, "\n")] = '\0';
    if (strcmp(input, "debug") == 0) {
        printf("Debug mode is disabled in production. Using normal mode.\n");
        run_secure_diagnostic(0);
    }
    else if (strcmp(input, "advanced") == 0) {
        run_secure_diagnostic(1);
    }
    else {
        run_secure_diagnostic(0);
    }
}

void run_secure_diagnostic(int diagnostic_level)
{
    printf("Running diagnostic...\n");
    sleep(1);
    printf("Performing system health check...\n");
    sleep(1);
    if (diagnostic_level > 0) {
        printf("Running advanced diagnostics...\n");
        sleep(1);
        printf("Diagnostic code: %d\n", rand() % 1000);
    }
    printf("System health: OK\n");
    printf("Diagnostic complete.\n");
}
