/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#include "../include/utils.h"
#include <sys/stat.h>

#include <errno.h>
#include <stdio.h>

int file_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file) {
        fclose(file);
        return 1;
    }
    if (errno == EACCES) {
        fprintf(stderr, "nm: %s: Permission denied\n", filename);
        return 0;
    }
    if (errno == ENOENT)
        fprintf(stderr, "nm: '%s': No such file\n", filename);
    else
        fprintf(stderr, "nm: %s: Error: %s\n", filename, strerror(errno));
    return 0;
}

size_t get_file_size(const char *filename)
{
    struct stat st;

    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return 0;
}

void print_usage(const char *program_name)
{
    printf("Usage: %s [file...]\n", program_name);
}
