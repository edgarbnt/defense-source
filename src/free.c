/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** free.c
*/

#include "../include/my.h"

void free_array(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return;
    while (arr[i] != NULL) {
        free(arr[i]);
        i ++;
    }
    free(arr);
}

void free_end(struct maze_s *maze)
{
    struct room_s *tmp = maze->room;
    struct room_s *tmp2 = maze->room;
    struct link_s *tmp3 = NULL;

    for (struct link_s *tmp4 = NULL; tmp != NULL; tmp = tmp2) {
        tmp2 = tmp->next;
        free(tmp->name);
        for (tmp3 = tmp->links; tmp3 != NULL; tmp3 = tmp4) {
            tmp4 = tmp3->next;
            free(tmp3);
        }
        free(tmp);
    }
    free(maze->start);
    free(maze->end);
    free(maze->buf);
    free(maze);
}

void free_links(link_t *links)
{
    for (link_t *prev = NULL; links; free(prev)) {
        prev = links;
        links = links->next;
    }
}

void free_robots(robot_t *robots)
{
    for (int i = 0; i < robots->path_nbr; i++)
        free(robots->ids[i]);
    free(robots->ids);
    free(robots->jobs);
    free(robots);
}
