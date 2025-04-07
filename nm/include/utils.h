/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#ifndef UTILS_H
    #define UTILS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

int file_exists(const char *filename);
size_t get_file_size(const char *filename);
void print_usage(const char *program_name);

#endif /* UTILS_H */
