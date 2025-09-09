##
## EPITECH PROJECT, 2025
## B-CPE-200 - A-MAZE-D
## File description:
## Makefile
##

NAME    = amazed

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -Iinclude

SRC     = $(shell find src -type f -name "*.c")
OBJ     = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
