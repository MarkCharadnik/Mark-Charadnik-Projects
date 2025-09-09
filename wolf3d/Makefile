##
## EPITECH PROJECT, 2025
## wolf3D
## File description:
## Makefile for building wolf3D
##

NAME	= wolf3d

SRC	= \
	  src/main.c \
	  src/load_map.c \
	  src/raycast.c \
	  src/draw.c \
	  src/movement.c \
	  src/event.c \
	  src/rotate.c \
	  src/error.c \
	  src/clock.c \
	  src/game_loop.c \
	  src/init_wolf.c \
	  src/hud.c \
	  src/menu.c \
	  src/settings.c \
	  src/save.c \
	  src/append_line.c \
	  src/draw_weapon.c \
	  src/draw_medkit.c \
	  src/particles.c  \
	  src/draw_particles.c \
	  src/minimap.c 

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

CC	= gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
