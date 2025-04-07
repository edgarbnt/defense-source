/*
** EPITECH PROJECT, 2025
** nm
** File description:
** file
*/

#ifndef ERROR_HANDLER_H
    #define ERROR_HANDLER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

void fatal_error(const char *message);
void file_error(const char *filename, const char *message);
void format_error(const char *filename);

#endif /* ERROR_HANDLER_H */
