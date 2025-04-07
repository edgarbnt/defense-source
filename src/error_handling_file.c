/*
** EPITECH PROJECT, 2023
** read in file and error handling
** File description:
** error handling
*/

#include "../include/my.h"

static int check_three_numbers_numerics(char **numbers, int k)
{
    for (int j = 0; numbers[k][j] != 0; j++) {
        if (numbers[k][j] < 48 || numbers[k][j] > 57) {
            free_array(numbers);
            return 84;
        }
    }
    return 0;
}

static int three_numbers(char *line, struct maze_s *maze_struct)
{
    char **numbers = my_str_to_word_array(line, " ");
    int i = 0;

    numbers = remove_comment(&numbers);
    for (i = 0; numbers[i] != NULL; i++);
    if (i != 3) {
        free_array(numbers);
        return 84;
    }
    for (int k = 1; numbers[k]; k++)
        if (check_three_numbers_numerics(numbers, k) == 84)
            return 84;
    if (check_room_names(numbers, maze_struct) == 84)
        return 84;
    if (check_coordinates(char_to_int(numbers[1]),
        char_to_int(numbers[2]), maze_struct) == 84)
        return 84;
    free_array(numbers);
    return 0;
}

static int check_start_end(
    const char *line, struct maze_s *maze_struct,
    int *line_after_end, int *line_after_start)
{
    static int start = 0;
    static int end = 0;

    if (my_strcmp(line, "##start") == 0) {
        start++;
        (*line_after_start) = 1;
        maze_struct->nb_start++;
    } else if (my_strcmp(line, "##end") == 0) {
        end++;
        (*line_after_end) = 1;
        maze_struct->nb_end++;
    }
    if (start > 1 || end > 1)
        return 84;
    return 0;
}

static int check_command(char *line, struct maze_s *maze_struct)
{
    static int line_after_start = 0;
    static int line_after_end = 0;

    if (line_after_start == 1) {
        if (three_numbers(line, maze_struct) == 84)
            return 84;
        maze_struct->start = my_strdup(line);
        line_after_start = 2;
    }
    if (line_after_end == 1) {
        if (three_numbers(line, maze_struct) == 84)
            return 84;
        maze_struct->end = my_strdup(line);
        line_after_end = 2;
    }
    return check_start_end(
        line, maze_struct, &line_after_end, &line_after_start);
}

static int is_there_space(char *line)
{
    for (int i = 0; line[i] != 0; i++) {
        if (line[i] == ' ') {
            return 84;
        }
    }
    return 0;
}

int check_three_or_two_numbers(char *line, struct maze_s *maze_struct)
{
    int i;
    int is_there_hashtag = 0;
    char **numbers = my_str_to_word_array(line, "- \n");

    numbers = remove_comment(&numbers);
    if (three_numbers(line, maze_struct) == 84) {
        for (i = 0; numbers[i] != NULL; i++);
        if (((i < 2) || (is_there_space(line) == 84)) ||
            check_room_tunnel_exist(numbers, maze_struct) == 84) {
            free_array(numbers);
            return 84;
        }
    } else
        free_array(numbers);
    return 0;
}

int check_first_line(
    char *line, struct maze_s *maze_struct, int *is_first_line_nb_robot)
{
    (*is_first_line_nb_robot) = 0;
    for (int i = 0; line[i] != 0; i++)
        if ((line[i] < 48 || line[i] > 57)) {
            return 84;
        }
    maze_struct->nb_robot = char_to_int(line);
    return 0;
}

int error_handling(char *line, struct maze_s *maze_struct)
{
    static int is_first_line_nb_robot = 1;
    int count_dash = 0;

    if (line[0] == '#' && my_strcmp(line, "##start") != 0 &&
        my_strcmp(line, "##end") != 0) {
        return 0;
    }
    for (int i = 0; line[i] != 0 && line[i] != '#'; i++)
        count_dash += (line[i] == '-') ? 1 : 0;
    if (count_dash > 1)
        return 84;
    if (is_first_line_nb_robot == 1)
        return check_first_line(line, maze_struct, &is_first_line_nb_robot);
    if (check_command(line, maze_struct) == 84)
        return 84;
    if (line[0] != '#' && check_three_or_two_numbers(line, maze_struct) == 84)
        return 84;
    return 0;
}
