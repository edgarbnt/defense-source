/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** char_to_int.c
*/

#include "../../include/my.h"

int char_to_int(char *nbr)
{
    int nbr_int = 0;
    int i = 0;
    int div = 1;

    while (nbr[i] != '\0' && nbr[i] != '.') {
        nbr_int += (nbr[i] - 48);
        i ++;
        if (nbr[i] != '\0')
            nbr_int *= 10;
    }
    while (nbr[i] != '\0') {
        i++;
        div *= 10;
        nbr_int += (nbr[i] - 48);
        if (nbr[i] != '\0')
            nbr_int *= 10;
    }
    nbr_int = nbr_int / div;
    return nbr_int;
}
