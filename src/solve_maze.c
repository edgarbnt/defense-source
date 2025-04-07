/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "../include/my.h"

char add_link(link_t **links, room_t *room)
{
    link_t *link = malloc(sizeof(*link));

    if (!link)
        return 0;
    link->link = room;
    link->next = *links;
    *links = link;
    return 1;
}

static int get_path_count(struct maze_s *maze_s)
{
    int start_links = 0;
    int end_links = 0;

    for (link_t *link = maze_s->start_node->links;
        link; link = link->next)
        start_links++;
    for (link_t *link = maze_s->end_node->links;
        link; link = link->next)
        end_links++;
    return start_links < end_links ? start_links : end_links;
}

static char invert_paths(link_t **paths, int path_count)
{
    int ret = 1;
    link_t *rev_path;

    for (int i = 0; i < path_count; i++) {
        rev_path = NULL;
        for (link_t *head = paths[i]; ret && head; head = head->next)
            ret = add_link(&rev_path, head->link);
        if (!ret)
            return 0;
        free_links(paths[i]);
        paths[i] = rev_path;
    }
    return 1;
}

int solve_maze(struct maze_s *maze_s)
{
    link_t **paths;
    int path_count = get_path_count(maze_s);

    if (!path_count)
        return 0;
    paths = malloc(sizeof(link_t *) * path_count);
    if (!paths)
        return 84;
    for (int i = 0; i < path_count; i++)
        paths[i] = NULL;
    if (!eval_scores(maze_s->end_node) ||
        !find_paths(paths, path_count,
        maze_s->start_node, maze_s->end_node) ||
        !invert_paths(paths, path_count) ||
        !move_robots(paths, path_count, maze_s))
        return 84;
    for (int i = 0; i < path_count; i++)
        free_links(paths[i]);
    free(paths);
    return 0;
}
