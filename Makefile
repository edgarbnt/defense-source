##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

SRC 	= 	src/main.c			\
		src/error_handling_file.c	\
		src/parsing_maze.c		\
		src/free.c			\
		src/handle_db_array.c		\
		src/start_end.c			\
		src/rooms.c			\
		src/check_room_already_exist.c	\
		src/print_comments.c		\
		src/solve_maze.c		\
		src/eval_rooms.c		\
		src/find_paths.c		\
		src/move_robots.c		\
		src/buffer.c			\

LIB 	= 	lib/my/functions_mini_printf.c	\
		lib/my/my_str_to_word_array.c	\
		lib/my/my_strcat.c		\
		lib/my/my_strcmp.c		\
		lib/my/my_strncmp.c		\
		lib/my/my_strdup.c		\
		lib/my/mini_printf.c		\
		lib/my/my_str_isnum.c		\
		lib/my/char_to_int.c		\

TESTS	=	src/error_handling_file.c	\
		src/parsing_maze.c		\
		src/free.c			\
		src/handle_db_array.c		\
		src/start_end.c			\
		src/rooms.c			\
		src/check_room_already_exist.c	\
		src/print_comments.c		\
		src/solve_maze.c		\
		src/eval_rooms.c		\
		src/find_paths.c		\
		src/move_robots.c		\
		src/buffer.c			\

OBJ 	= 	$(SRC:.c=.o)

NAME	= 	amazed

CFLAGS	=      -Wall -Wextra -Werror -g3
CFLAGS	+=     -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
FAST	=      -fno-builtin -Ofast -flto -march=native

all:		fast

libmy.a:
		make -C lib/my

tests_run:	libmy.a
		gcc -o unit_tests $(TESTS) tests/tests_amazed.c \
		--coverage -lcriterion -L lib/my/ -lmy
		./unit_tests

$(NAME):	$(OBJ) $(LIB) libmy.a
		gcc $(CFLAGS) -o $(NAME) $(OBJ) -L lib/my/ -lmy

fast:		$(SRC)
		gcc $(CFLAGS) -o $(NAME) $(LIB) $(SRC) $(FAST)

clean:
		make clean -C lib/my
		rm -f $(OBJ) *.gcda *.gcno

fclean:		clean
		make fclean -C lib/my
		rm -f $(NAME) unit_tests

re:		fclean all
