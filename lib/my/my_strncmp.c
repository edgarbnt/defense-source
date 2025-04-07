/*
** EPITECH PROJECT, 2023
** my_strncmp.c
** File description:
** task07
*/

#include "../../include/my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    for (int a = 0; a < n; a++){
        if (s1[a] < s2[a]){
            return 1;
        }
        if (s1[a] > s2[a]){
            return -1;
        }
    }
    return 0;
}
