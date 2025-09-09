/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** check_cooling_pressure
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void load_data(char *data, size_t size)
{
    strncpy(data, "Pressure OK", size - 1);
    data[size - 1] = '\0';
}

static void log_pressure_status(const char *status)
{
    printf("Cooling pressure status: %s\n", status);
}

static void simulate_sensor_reading()
{
    printf("Simulating sensor reading...\n");
    sleep(1);
    printf("Sensor reading complete.\n");
}

void check_cooling_pressure()
{
    size_t BUFFER_SIZE = 16;
    char *data = (char *)malloc(BUFFER_SIZE);
    char sensitive_info[32] = "{REDACTED}";
    int pressure_ok;
    char temp_buffer[32];

    if (!data) {
        printf("Memory allocation failed\n");
        return;
    }
    load_data(data, BUFFER_SIZE);
    printf("Cooling pressure check in progress...\n");
    sleep(2);
    simulate_sensor_reading();
    printf("Checking cooling pressure...\n");
    sleep(1);
    pressure_ok = (strcmp(data, "Pressure OK") == 0);
    log_pressure_status(data);
    memset(sensitive_info, 0, sizeof(sensitive_info));
    free(data);
    data = NULL;
    sleep(3);
    if (!pressure_ok)
        printf("Warning: Cooling pressure issue detected\n");
    snprintf(temp_buffer, sizeof(temp_buffer), "Temporary data: %d", rand() % 100);
    printf("Temporary buffer: %s\n", temp_buffer);
    simulate_sensor_reading();
    printf("Cooling pressure check complete.\n");
}
