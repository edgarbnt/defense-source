/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "../include/my.h"

void buf_scpy(char *buf, int *buf_i, char *data)
{
    for (int i = 0; data[i];) {
        if (*buf_i >= BUF_SIZE) {
            write(1, buf, *buf_i);
            *buf_i = 0;
        }
        for (; data[i] && *buf_i < BUF_SIZE; i++) {
            buf[*buf_i] = data[i];
            (*buf_i)++;
        }
    }
}

void buf_ccpy(char *buf, int *buf_i, char data)
{
    if (*buf_i >= BUF_SIZE) {
        write(1, buf, *buf_i);
        *buf_i = 0;
    }
    if (*buf_i < BUF_SIZE) {
        buf[*buf_i] = data;
        (*buf_i)++;
    }
}

void buf_add_move(robot_t *robot_s, maze_t *maze_s, int i)
{
    if (!robot_s->first_field)
        buf_ccpy(maze_s->buf, &maze_s->buf_i, ' ');
    robot_s->first_field = 0;
    buf_ccpy(maze_s->buf, &maze_s->buf_i, 'P');
    buf_scpy(maze_s->buf, &maze_s->buf_i, robot_s->ids[i]);
    buf_ccpy(maze_s->buf, &maze_s->buf_i, '-');
    buf_scpy(maze_s->buf, &maze_s->buf_i, robot_s->jobs[i]->link->name);
}

int int_to_str(char *str, int nbr)
{
    int i = 0;
    int start = -1;
    char tmp;

    if (!nbr) {
        str[0] = '0';
        str[1] = '\0';
        return 1;
    }
    for (; nbr; nbr /= 10) {
        str[i] = (nbr % 10) + '0';
        i++;
    }
    str[i] = '\0';
    for (int end = i - 1; ++start < end; end--) {
        tmp = str[start];
        str[start] = str[end];
        str[end] = tmp;
    }
    return i;
}
