/*
** EPITECH PROJECT, 2025
** ref-G-SEC-210-project
** File description:
** load_config
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

char *get_admin_password()
{
    const char *env_pass = getenv("ADMIN_PASSWORD");
    return env_pass ? env_pass : "";
}

int check_password(const char *input)
{
    char *stored = get_admin_password();
    size_t input_len = input ? strlen(input) : 0;
    size_t stored_len = stored ? strlen(stored) : 0;
    int result = 0;

    for (size_t i = 0; i < stored_len; i++)
        result |= (i < input_len ? input[i] : 0) ^ stored[i];
    return (result == 0) && (input_len == stored_len);
}

void load_config(void)
{
    int fd;
    char *buffer;
    size_t file_size;
    ssize_t bytes_read;

    printf("Loading configuration file from ./config.ini\n");
    fd = open("./config.ini", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open config file");
        return;
    }
    file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    if (file_size <= 0) {
        printf("Empty or invalid config file\n");
        close(fd);
        return;
    }
    buffer = malloc(file_size + 1);
    if (!buffer) {
        printf("Memory allocation failed\n");
        close(fd);
        return;
    }
    bytes_read = read(fd, buffer, file_size);
    close(fd);
    if (bytes_read < 0) {
        perror("Failed to read config file");
        free(buffer);
        return;
    }
    buffer[bytes_read] = '\0';
    if (strstr(buffer, "[admin]") != NULL) {
        printf("Admin section found in config\n");
    } else {
        printf("No admin section found in config\n");
    }
    free(buffer);
}
