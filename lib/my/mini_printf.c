/*
** EPITECH PROJECT, 2023
** mini_printf
** File description:
** a simple version of printf
*/

#include "../../include/my.h"

void format_percentage(const char format, va_list args,
    int *char_printed, int fd)
{
    if (format == 'i')
        my_put_nbr_long(va_arg(args, long int), char_printed, fd);
    if (format == 'c') {
        my_putchar(va_arg(args, int), fd);
        (*char_printed)++;
    }
    if (format == 'd')
        my_put_nbr(va_arg(args, int), char_printed, fd);
    if (format == 's')
        my_putstr(va_arg(args, char const *), char_printed, fd);
    if (format == '%') {
        write(fd, "%", 1);
        (*char_printed)++;
    }
}

int mini_printf(int fd, const char *format, ...)
{
    va_list args;
    int sentence_count = 0;
    int char_printed = 0;

    va_start(args, format);
    while (format[sentence_count] != '\0') {
        if (format[sentence_count] == '%') {
            format_percentage(format[sentence_count + 1],
                args, &char_printed, fd);
            sentence_count += 2;
        } else {
            write(fd, &format[sentence_count], 1);
            sentence_count ++;
            char_printed ++;
        }
    }
    va_end(args);
    return char_printed;
}
