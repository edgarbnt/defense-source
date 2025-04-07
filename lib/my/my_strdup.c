/*
** EPITECH PROJECT, 2023
** my_strdup
** File description:
** function that allocates memory and copies
** the string given as argument in it.
*/

#include <stdlib.h>
#include "../../include/my.h"

char *my_strdup(char const *src)
{
    char *str;
    int i;
    int len = my_strlen(src);

    str = malloc(sizeof(char) * (len + 1));
    i = 0;
    while (i < len) {
        str[i] = src[i];
        i ++;
    }
    str[i] = '\0';
    return str;
}
