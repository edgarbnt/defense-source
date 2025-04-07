##
## EPITECH PROJECT, 2023
## B-CPE-101-LIL-1-1-myprintf-mathilde.lekens
## File description:
## Makefile
##

SRC = 	my_strcat.c	\
		my_strcmp.c	\
		my_strncmp.c	\
		my_strdup.c	\
		char_to_int.c \
		# my_str_isnum.c	\
		# my_str_to_word_array.c	\
		# functions_mini_printf.c	\
		# mini_printf.c	\

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
