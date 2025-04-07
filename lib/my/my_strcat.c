/*
** EPITECH PROJECT, 2023
** strcat
** File description:
** copy result of strcat function
*/

#include "../../include/my.h"

char *my_strcat(char *dest, const char *src)
{
    int taille = my_strlen(dest);
    int taille2 = my_strlen(src);
    int taille3 = 0;

    for (; taille3 < taille2; taille3++) {
        dest[taille] = src[taille3];
        taille++;
    }
    dest[taille] = '\0';
    return dest;
}
