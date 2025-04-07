/*
** EPITECH PROJECT, 2025
** objdump
** File description:
** file
*/

#ifndef UTILS_H
    #define UTILS_H

    #include <stdbool.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

bool is_option(const char *arg);
bool has_option(const char *arg, char option);
void print_usage(void);

#endif /* UTILS_H */
