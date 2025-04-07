/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "../include/my.h"

static robot_t *get_robots(link_t **paths, int path_count, int robots_nbr)
{
    robot_t *robot_s = malloc(sizeof(robot_t));

    if (!robot_s)
        return NULL;
    robot_s->jobs = malloc(sizeof(link_t *) * path_count);
    robot_s->ids = malloc(sizeof(char *) * path_count);
    robot_s->paths = paths;
    robot_s->robot_nbr = robots_nbr;
    robot_s->path_nbr = path_count;
    robot_s->current_id = path_count;
    robot_s->first_field = 1;
    robot_s->end_flag = 1;
    if (!robot_s->jobs || !robot_s->ids)
        return NULL;
    for (int i = 0; i < robot_s->path_nbr; i++) {
        robot_s->ids[i] = malloc(sizeof(char) * 12);
        if (!robot_s->ids[i])
            return NULL;
    }
    return robot_s;
}

static char init_robots(robot_t *robot_s)
{
    if (!robot_s)
        return 0;
    for (int i = 0; i < robot_s->path_nbr; i++) {
        if (i >= robot_s->robot_nbr) {
            robot_s->jobs[i] = NULL;
        } else {
            robot_s->jobs[i] = robot_s->paths[i];
            int_to_str(robot_s->ids[i], i + 1);
        }
    }
    return 1;
}

static char should_move(robot_t *robot_s, maze_t *maze_s, int *i)
{
    if (*i >= robot_s->path_nbr) {
        buf_ccpy(maze_s->buf, &maze_s->buf_i, '\n');
        if (!robot_s->end_flag)
            return 0;
        robot_s->first_field = 1;
        robot_s->end_flag = 0;
        *i = 0;
    }
    return 1;
}

static char move_round(robot_t *robot_s, int i)
{
    if (robot_s->jobs[i]->next) {
        robot_s->jobs[i] = robot_s->jobs[i]->next;
        return 1;
    }
    if (robot_s->current_id < robot_s->robot_nbr) {
        robot_s->jobs[i] = robot_s->paths[i];
        robot_s->current_id++;
        int_to_str(robot_s->ids[i], robot_s->current_id);
        return 1;
    }
    robot_s->jobs[i] = NULL;
    return 0;
}

char move_robots(link_t **paths, int path_count, maze_t *maze_s)
{
    robot_t *robot_s = get_robots(paths, path_count, maze_s->nb_robot);

    if (!init_robots(robot_s))
        return 0;
    for (int i = 0; should_move(robot_s, maze_s, &i); i++) {
        if (!robot_s->jobs[i])
            continue;
        buf_add_move(robot_s, maze_s, i);
        robot_s->end_flag += move_round(robot_s, i);
    }
    if (maze_s->buf_i)
        write(1, maze_s->buf, maze_s->buf_i);
    free_robots(robot_s);
    return 1;
}
