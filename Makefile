##
## EPITECH PROJECT, 2023
## NM OBJDUMP
## File description:
## Makefile
##

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include
RM = rm -f

NM_SRC_DIR = nm/src
NM_INCLUDE_DIR = nm/include
NM_SRC = $(NM_SRC_DIR)/main.c \
         $(NM_SRC_DIR)/elf_parser.c \
         $(NM_SRC_DIR)/error_handler.c \
         $(NM_SRC_DIR)/utils.c \
         $(NM_SRC_DIR)/symbol/symbol_table.c \
         $(NM_SRC_DIR)/symbol/symbol_type.c \
         $(NM_SRC_DIR)/symbol/symbol_utils.c \
         $(NM_SRC_DIR)/symbol/symbol_display.c \
         $(NM_SRC_DIR)/symbol/symbol_processing.c

NM_OBJ = $(NM_SRC:.c=.o)
NM_NAME = my_nm

OBJDUMP_SRC_DIR = objdump/src
OBJDUMP_INCLUDE_DIR = objdump/include
OBJDUMP_SRC = $(OBJDUMP_SRC_DIR)/main.c \
              $(OBJDUMP_SRC_DIR)/elf_parser.c \
              $(OBJDUMP_SRC_DIR)/error_handler.c \
              $(OBJDUMP_SRC_DIR)/file_header.c \
              $(OBJDUMP_SRC_DIR)/utils.c \
              $(OBJDUMP_SRC_DIR)/get_machines.c \
              $(OBJDUMP_SRC_DIR)/section_display.c \

OBJDUMP_OBJ = $(OBJDUMP_SRC:.c=.o)
OBJDUMP_NAME = my_objdump

all: nm objdump

nm: $(NM_NAME)

objdump: $(OBJDUMP_NAME)

$(NM_NAME): $(NM_OBJ)
	$(CC) -o $(NM_NAME) $(NM_OBJ)

$(OBJDUMP_NAME): $(OBJDUMP_OBJ)
	$(CC) -o $(OBJDUMP_NAME) $(OBJDUMP_OBJ)

clean:
	$(RM) $(NM_OBJ)
	$(RM) $(OBJDUMP_OBJ)

fclean: clean
	$(RM) $(NM_NAME)
	$(RM) $(OBJDUMP_NAME)

re: fclean all

tests_run:
	@echo "test rule"

.PHONY: all nm objdump clean fclean re tests_run
