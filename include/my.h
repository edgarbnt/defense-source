/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** my.h
*/

#ifndef AMAZED_MY_H
    #define AMAZED_MY_H

    #include <stdlib.h>
    #include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <string.h>
    #include <errno.h>
    #include <sys/wait.h>
    #include <stdarg.h>
    #include <limits.h>
    #include <stdbool.h>

    #define BUF_SIZE 128 * 1024

enum steps {
    NONE = 0,
    NB_ROBOT,
    ROOMS,
    TUNNELS,
    MOVES
};

typedef struct link_s {
    struct room_s *link;
    struct link_s *next;
} link_t;

typedef struct room_s {
    char *name;
    int x;
    int y;
    int score;
    char taken;
    link_t *links;
    struct room_s *next;
} room_t;

typedef struct maze_s {
    char *start;
    char *end;
    struct room_s *start_node;
    struct room_s *end_node;
    int nb_start;
    int nb_end;
    int nb_robot;
    enum steps step;
    char *buf;
    int buf_i;
    struct room_s *room;
} maze_t;

typedef struct robot_s {
    char **ids;
    link_t **jobs;
    link_t **paths;
    int robot_nbr;
    int path_nbr;
    int current_id;
    char first_field;
    char end_flag;
} robot_t;

int solve_maze(struct maze_s *maze_s);
char add_link(link_t **links, room_t *room);
char eval_scores(room_t *end);
char find_paths(link_t **paths, int nbr, room_t *start, room_t *end);
char move_robots(link_t **paths, int path_count, maze_t *maze_s);
void buf_scpy(char *buf, int *buf_i, char *data);
void buf_ccpy(char *buf, int *buf_i, char data);
void buf_add_move(robot_t *robot_s, maze_t *maze_s, int i);
int int_to_str(char *str, int nbr);
void free_links(link_t *links);
void free_robots(robot_t *robots);
int check_room_names(char **numbers, maze_t *maze_struct);
int check_coordinates(int x, int y, maze_t *maze);
int check_room_tunnel_exist(char **numbers, maze_t *maze_struct);
int error_handling(char *line, struct maze_s *maze_struct);
int parsing_maze(void);
int char_to_int(char *nbr);
void free_array(char **arr);
bool is_start_end(char *line);
int my_strlen(char const *str);
void my_putchar(char c, int fd);
char *my_strdup(char const *src);
int my_str_isnum(char const *str);
int len_db_array(char **db_array);
void free_end(struct maze_s *maze);
char **create_matrix(struct maze_s *maze);
char **remove_comment(char ***command);
char **add_in_array(char **array, char *link);
int my_strcmp(char const *s1, char const *s2);
int mini_printf(int fd, const char *format, ...);
char **my_str_to_word_array(char *str, char *del);
int my_put_nbr(int nb, int *char_printed, int fd);
int my_strncmp(char const *s1, char const *s2, int n);
void comments(struct maze_s *maze_struct, char *line);
int my_putstr(char const *str, int *char_printed, int fd);
int error_handling(char *line, struct maze_s *maze_struct);
void add_room(struct maze_s **maze, char *name, char *link);
int my_put_nbr_long(long int nb, int *char_printed, int fd);
void add_room_coord(struct maze_s **maze, char *name, char *x, char *y);
void add_start_end(struct maze_s **maze, char *name, struct room_s **new_room);

#endif
