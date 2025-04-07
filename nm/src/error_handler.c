/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#include "../include/error_handler.h"

void fatal_error(const char *message)
{
    fprintf(stderr, "Error: %s\n", message);
    exit(84);
}

void file_error(const char *filename, const char *message)
{
    fprintf(stderr, "Error: %s: %s\n", filename, message);
    exit(84);
}

void format_error(const char *filename)
{
    fprintf(stderr, "nm: %s: file format not recognized\n", filename);
    exit(84);
}
