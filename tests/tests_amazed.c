/*
** EPITECH PROJECT, 2024
** amazed_solved
** File description:
** tests_error_handling.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

void test_error_handling(char *file)
{
    FILE *old_stdin = stdin;
    stdin = fopen(file, "r");
    int expected_value = 84;
    int actual_value = parsing_maze();

    cr_assert_eq(actual_value, expected_value, "Expected %d but got %d", expected_value, actual_value);
    fclose(stdin);
    stdin = old_stdin;
}

void test_normal_exec(char *file)
{
    FILE *old_stdin = stdin;
    stdin = fopen(file, "r");
    int expected_value = 0;
    int actual_value = parsing_maze();

    cr_assert_eq(actual_value, expected_value, "Expected %d but got %d", expected_value, actual_value);
    fclose(stdin);
    stdin = old_stdin;
}

Test(error_maze, null_file, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/null_file");
}

Test(error_maze, return_character, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/return");
}

Test(error_maze, wrong_robots, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_robot");
}

Test(error_maze, wrong_robots_2, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_robot_2");
}

Test(error_maze, room_letter_coord_y, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_y");
}

Test(error_maze, room_letter_coord_y_2, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_y_2");
}

Test(error_maze, room_letter_coord_x, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_x");
}

Test(error_maze, room_letter_coord_x_2, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/wrong_x_2");
}

Test(error_maze, too_many_arg, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_many_arg");
}

Test(error_maze, too_few_arg, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_few_arg");
}

Test(error_maze, missing_start, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_missing_start");
}

Test(error_maze, missing_end, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_missing_end");
}

Test(error_maze, same_coordinates, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_same_coordinates");
}

Test(error_maze, same_names, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_same_names");
}

Test(error_maze, two_start, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/two_start");
}

Test(error_maze, two_ends, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/two_ends");
}

Test(error_maze, tunnel_exist_1, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/tunnel_no1_exist");
}

Test(error_maze, tunnel_exist_2, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/tunnel_no2_exist");
}

Test(error_maze, too_many_arg_start, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_many_args_start");
}

Test(error_maze, too_few_arg_start, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_few_args_start");
}

Test(error_maze, too_many_arg_end, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_many_args_end");
}

Test(error_maze, missing_robot, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/missing_robot");
}

Test(error_maze, too_few_arg_end, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/room_too_few_args_end");
}

Test(error_maze, invalid_tunnel_dash, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/invalid_tunnel_dash");
}

Test(error_maze, invalid_tunnel_one_arg, .init = redirect_all_std)
{
    test_error_handling("tests/files_error_handling/invalid_tunnel_one_arg");
}

Test(comments_maze, comment_before_robot, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/comment_before_robot");
}

Test(comments_maze, comment_before_start, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/comment_before_start");
}

Test(comments_maze, comment_before_end, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/comment_before_end");
}

Test(comments_maze, comment_before_room, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/comment_before_room");
}

Test(comments_maze, comment_before_tunnel, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/comment_before_tunnel");
}

Test(comments_maze, normal_execution, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/normal_file");
}

Test(comments_maze, room_next_null, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/normal_file_2");
}

Test(comments_maze, big_file, .init = redirect_all_std)
{
    test_normal_exec("tests/files_normal_execution/laby");
}
