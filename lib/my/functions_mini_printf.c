/*
** EPITECH PROJECT, 2023
** functions_mini_printf
** File description:
** function for mini_printf
** (my_putstr, my_put_nbr, my_putchar)
*/

#include "../../include/my.h"

void my_putchar(char c, int fd)
{
    write(fd, &c, 1);
    return;
}

int my_put_nbr(int nb, int *char_printed, int fd)
{
    int tmp1;

    if (nb < 0){
        nb = nb * -1;
        my_putchar('-', fd);
        (*char_printed)++;
    }
    if (nb > 9){
        tmp1 = nb % 10;
        my_put_nbr((nb - tmp1) / 10, char_printed, fd);
        my_putchar(tmp1 + 48, fd);
        (*char_printed)++;
    } else {
        my_putchar(nb + 48, fd);
        (*char_printed)++;
    }
    return 0;
}

int my_put_nbr_long(long int nb, int *char_printed, int fd)
{
    int tmp1;

    if (nb < 0){
        nb = nb * -1;
        my_putchar('-', fd);
        (*char_printed)++;
    }
    if (nb > 9){
        tmp1 = nb % 10;
        my_put_nbr_long((nb - tmp1) / 10, char_printed, fd);
        my_putchar(tmp1 + 48, fd);
        (*char_printed)++;
    } else {
        my_putchar(nb + 48, fd);
        (*char_printed)++;
    }
    return 0;
}

int my_putstr(char const *str, int *char_printed, int fd)
{
    int compteur = 0;

    while (str[compteur] != '\0'){
        my_putchar(str[compteur], fd);
        (*char_printed)++;
        compteur ++;
    }
    return 0;
}

int my_strlen(char const *str)
{
    int compteur = 0;

    while (str[compteur] != '\0'){
        compteur ++;
    }
    return compteur;
}
