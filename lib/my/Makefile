##
## EPITECH PROJECT, 2023
## B-CPE-101-LIL-1-1-myprintf-mathilde.lekens
## File description:
## Makefile
##

SRC = 	functions_mini_printf.c	\
		my_str_to_word_array.c	\
		my_strcat.c	\
		my_strcmp.c	\
		my_strncmp.c	\
		my_strdup.c	\
		mini_printf.c	\
		my_str_isnum.c	\
		char_to_int.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

CFLAGS += -g

all:	libmy.a

libmy.a:	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean libmy.a
