/*
** EPITECH PROJECT, 2023
** my_str_isnum
** File description:
** eturns 1 if the string passed as parameter only
** contains lowercase alphabetical char-
** acters and 0 otherwise
*/

#include "../../include/my.h"

static int lenstr(char const *str)
{
    int compteur = 0;

    while (str[compteur] != '\0'){
        compteur ++;
    }
    return compteur;
}

void nonum(char const *str, int compteur, int *value)
{
    if (str[compteur] < 48 || str[compteur] > 57){
        *value = 0;
        return;
    }
}

int my_str_isnum(char const *str)
{
    int len = lenstr(str);
    int value = 1;

    for (int compteur = 0; compteur < len; compteur++)
        nonum(str, compteur, &value);
    return value;
}
