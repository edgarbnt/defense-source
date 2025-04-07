/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** rooms.c
*/

#include "../include/my.h"

static void add_link_ptr(struct room_s *node_to_add, link_t **links)
{
    link_t *new_link = malloc(sizeof(link_t));
    link_t *tmp = *links;

    new_link->link = node_to_add;
    new_link->next = NULL;
    if (*links == NULL) {
        *links = new_link;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_link;
}

void add_room(struct maze_s **maze, char *name, char *link)
{
    struct room_s *tmp_maze = (*maze)->room;
    struct room_s *tmp_maze2 = (*maze)->room;

    while (tmp_maze != NULL && my_strcmp(tmp_maze->name, name) != 0)
        tmp_maze = tmp_maze->next;
    while (tmp_maze2 != NULL && my_strcmp(tmp_maze2->name, link) != 0)
        tmp_maze2 = tmp_maze2->next;
    if (tmp_maze == NULL || tmp_maze2 == NULL)
        return;
    add_link_ptr(tmp_maze2, &tmp_maze->links);
    add_link_ptr(tmp_maze, &tmp_maze2->links);
}

void add_room_coord_null(struct room_s **new_room,
    char *name, char *x, char *y)
{
    (*new_room)->name = my_strdup(name);
    (*new_room)->x = char_to_int(x);
    (*new_room)->y = char_to_int(y);
    (*new_room)->next = NULL;
    (*new_room)->links = NULL;
    (*new_room)->score = INT_MAX;
    (*new_room)->taken = 0;
}

struct room_s *append_room(struct room_s **new_room,
    char *name, char *x, char *y)
{
    (*new_room)->name = my_strdup(name);
    (*new_room)->x = char_to_int(x);
    (*new_room)->y = char_to_int(y);
    (*new_room)->links = NULL;
    (*new_room)->next = NULL;
    (*new_room)->score = INT_MAX;
    (*new_room)->taken = 0;
    return (*new_room);
}

void add_room_coord(struct maze_s **maze, char *name, char *x, char *y)
{
    struct room_s *new_room = malloc(sizeof(struct room_s));
    struct room_s *tmp_maze = (*maze)->room;

    if (tmp_maze == NULL) {
        add_room_coord_null(&new_room, name, x, y);
        add_start_end(maze, name, &new_room);
        (*maze)->room = new_room;
        return;
    }
    while (tmp_maze->next != NULL)
        tmp_maze = tmp_maze->next;
    tmp_maze->next = append_room(&new_room, name, x, y);
    add_start_end(maze, name, &new_room);
}
