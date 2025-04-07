/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** print_comments.c
*/

#include "../include/my.h"

void cut_comment(struct maze_s *maze, char *line)
{
    char *line_cut;
    int i = 0;

    if (my_strcmp(line, "##start") == 0 || my_strcmp(line, "##end") == 0) {
        buf_scpy(maze->buf, &maze->buf_i, line);
        buf_ccpy(maze->buf, &maze->buf_i, '\n');
        return;
    }
    for (; line[i] != '\0' && line[i] != '#'; i++);
    if (line[i] == '\0') {
        buf_scpy(maze->buf, &maze->buf_i, line);
        buf_ccpy(maze->buf, &maze->buf_i, '\n');
        return;
    }
    line_cut = malloc(sizeof(char) * (i + 1));
    for (int j = -1; ++j < i; line_cut[j] = line[j]);
    line_cut[i] = '\0';
    buf_scpy(maze->buf, &maze->buf_i, line_cut);
    buf_ccpy(maze->buf, &maze->buf_i, '\n');
    free(line_cut);
}

bool contain_char(char *line, char del)
{
    for (int i = 0; line[i]; i++)
        if (line[i] == del)
            return true;
    return false;
}

void print_command(struct maze_s *maze, char *line)
{
    if (maze->nb_robot != -1 && maze->step == NONE) {
        buf_scpy(maze->buf, &maze->buf_i, "#number_of_robots\n");
        maze->step++;
    }
    if (contain_char(line, '-') && maze->step == ROOMS) {
        buf_scpy(maze->buf, &maze->buf_i, "#tunnels\n");
        maze->step++;
    }
}

void comments(struct maze_s *maze, char *line)
{
    if (my_strcmp(line, "##start") != 0 && my_strcmp(line, "##end") != 0 &&
        line[0] == '#')
        return;
    print_command(maze, line);
    cut_comment(maze, line);
    if (maze->step == NB_ROBOT) {
        buf_scpy(maze->buf, &maze->buf_i, "#rooms\n");
        maze->step++;
    }
}
