/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** handle_db_array.c
*/

#include "../include/my.h"

int len_db_array(char **db_array)
{
    int i = 0;

    if (db_array == NULL)
        return 0;
    while (db_array[i] != NULL)
        i++;
    return i;
}

char **remove_comment(char ***command)
{
    char **new_command;
    int i = 0;

    for (; (*command)[i] != NULL && (*command)[i][0] != '#'; i++);
    new_command = malloc(sizeof(char *) * (i + 1));
    for (int j = 0; j < i; j++) {
        new_command[j] = my_strdup((*command)[j]);
    }
    new_command[i] = NULL;
    free_array((*command));
    return new_command;
}
