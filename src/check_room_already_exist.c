/*
** EPITECH PROJECT, 2023
** placeholder
** File description:
** check room or tunnel already exist
*/

#include "../include/my.h"

int check_coordinates(int x, int y, maze_t *maze_struct)
{
    struct room_s *tmp = maze_struct->room;

    while (tmp != NULL) {
        if (x == tmp->x && y == tmp->y)
            return 84;
        tmp = tmp->next;
    }
    return 0;
}

int check_room_names(char **numbers, maze_t *maze_struct)
{
    struct room_s *tmp = maze_struct->room;

    while (tmp != NULL) {
        if (my_strcmp(numbers[0], tmp->name) == 0) {
            free_array(numbers);
            return 84;
        }
        tmp = tmp->next;
    }
    return 0;
}

int check_room_tunnel_exist(char **numbers, maze_t *maze_struct)
{
    int room1 = 0;
    int room2 = 0;
    struct room_s *tmp = maze_struct->room;

    while (tmp != NULL) {
        if (my_strcmp(numbers[0], tmp->name) == 0)
            room1 = 1;
        if (my_strcmp(numbers[1], tmp->name) == 0)
            room2 = 1;
        tmp = tmp->next;
    }
    if (room1 == 0 || room2 == 0) {
        return 84;
    }
    free_array(numbers);
    return 0;
}
