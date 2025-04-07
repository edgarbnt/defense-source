/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** parsing_maze.c
*/

#include "../include/my.h"

char *retrieve_line(void)
{
    ssize_t read;
    size_t len = 0;
    char *maze = NULL;
    char **tab = NULL;

    read = getline(&maze, &len, stdin);
    if (read == -1) {
        free(maze);
        return NULL;
    }
    tab = my_str_to_word_array(maze, " \t\n");
    if (tab == NULL) {
        free_array(tab);
        free(maze);
        return NULL;
    }
    free_array(tab);
    if (maze[my_strlen(maze) - 1] == '\n')
        maze[my_strlen(maze) - 1] = '\0';
    return maze;
}

void parsing_position(char *maze, struct maze_s **maze_struct, int end)
{
    char **tab = my_str_to_word_array(maze, " -\t");
    int len;

    tab = remove_comment(&tab);
    len = len_db_array(tab);
    if (len == 3)
        add_room_coord(maze_struct, tab[0], tab[1], tab[2]);
    if (len == 2)
        add_room(maze_struct, tab[0], tab[1]);
    free_array(tab);
}

struct maze_s *init_maze_struct(void)
{
    struct maze_s *maze_struct = malloc(sizeof(struct maze_s));

    maze_struct->buf = malloc(sizeof(char) * BUF_SIZE);
    maze_struct->buf_i = 0;
    maze_struct->room = NULL;
    maze_struct->start = NULL;
    maze_struct->end = NULL;
    maze_struct->step = 0;
    maze_struct->nb_end = 0;
    maze_struct->nb_start = 0;
    maze_struct->nb_robot = -1;
    return maze_struct;
}

int loop_parsing(struct maze_s *maze_struct)
{
    char *maze = NULL;
    int end = -1;

    while (end == -1) {
        maze = retrieve_line();
        if (maze == NULL || my_strlen(maze) == 0)
            end = 0;
        if (end == -1 && error_handling(maze, maze_struct) == 84)
            end = 84;
        if (end == -1 && maze_struct->nb_robot == -1)
            maze_struct->nb_robot = char_to_int(maze);
        if (end == -1)
            comments(maze_struct, maze);
        if (maze != NULL) {
            parsing_position(maze, &maze_struct, end);
            free(maze);
        }
    }
    return end;
}

int parsing_maze(void)
{
    struct maze_s *maze_struct = init_maze_struct();
    int end = loop_parsing(maze_struct);

    if (end == 0 && maze_struct->step == TUNNELS)
        buf_scpy(maze_struct->buf, &maze_struct->buf_i, "#moves\n");
    if (end != 84 && (maze_struct->start == NULL || maze_struct->end == NULL))
        end = 84;
    if (end != 84)
        end = solve_maze(maze_struct);
    free_end(maze_struct);
    return end;
}
