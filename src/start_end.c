/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** start_end.c
*/

#include "../include/my.h"

void add_start(struct maze_s **maze, char *name, struct room_s **new_room)
{
    char **start_cut = NULL;

    start_cut = my_str_to_word_array((*maze)->start, " ");
    if (start_cut == NULL)
        return;
    if (start_cut[0] != NULL && my_strcmp(name, start_cut[0]) == 0) {
        (*maze)->start_node = *new_room;
    }
    free_array(start_cut);
}

void add_end(struct maze_s **maze, char *name, struct room_s **new_room)
{
    char **end_cut = my_str_to_word_array((*maze)->end, " ");

    if (end_cut == NULL)
        return;
    if (end_cut[0] != NULL && my_strcmp(name, end_cut[0]) == 0) {
        (*maze)->end_node = *new_room;
    }
    free_array(end_cut);
}

void add_start_end(struct maze_s **maze, char *name, struct room_s **new_room)
{
    if ((*maze)->start != NULL)
        add_start(maze, name, new_room);
    if ((*maze)->end != NULL)
        add_end(maze, name, new_room);
}
