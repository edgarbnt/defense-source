/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "../include/my.h"

static void get_best_link(room_t *cur_room, link_t **best_head)
{
    int best_score = INT_MAX;

    *best_head = NULL;
    for (link_t *head = cur_room->links; head; head = head->next) {
        if (!head->link->taken && (!*best_head ||
            head->link->score < best_score)) {
            best_score = head->link->score;
            *best_head = head;
        }
    }
}

static void handle_dead_end(link_t **paths, int i, room_t *rooms[3])
{
    link_t *aux;

    rooms[0]->taken = 1;
    if (paths[i]->next) {
        rooms[0] = paths[i]->next->link;
        aux = paths[i]->next;
        free(paths[i]);
        paths[i] = aux;
    } else {
        rooms[0] = rooms[1];
        free(paths[i]);
        paths[i] = NULL;
    }
}

static char find_distinct_path(link_t **paths, int i, room_t *rooms[3])
{
    int ret;
    link_t *best_head = NULL;

    while (rooms[0] && rooms[0] != rooms[2]) {
        get_best_link(rooms[0], &best_head);
        if (!best_head && !paths[i])
            return 1;
        if (!best_head) {
            handle_dead_end(paths, i, rooms);
            continue;
        }
        if (!add_link(&paths[i], best_head->link))
            return 0;
        best_head->link->taken = 1;
        rooms[0] = best_head->link;
    }
    return 1;
}

char find_paths(link_t **paths, int nbr, room_t *start, room_t *end)
{
    room_t *rooms[3] = {NULL, start, end};

    start->taken = 1;
    for (int i = 0; i < nbr; i++) {
        end->taken = 0;
        rooms[0] = start;
        if (!find_distinct_path(paths, i, rooms))
            return 0;
    }
    return 1;
}
