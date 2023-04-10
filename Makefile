# configure -> libmlx_Linux.a 

NAME	= cub3D

# SRCS = srcs/main.c srcs/check_input.c srcs/run_game.c
SRCS	= $(wildcard srcs/*.c)

OBJS	= $(SRCS:.c=.o)

INCLUDES	= includes/cub3D.h

CC	= cc

CFLAGS	= -Wall -Wextra -Werror -g3

MLX_LIB	= minilibx-linux/libmlx_Linux.a

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	cd minilibx-linux && ./configure

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -I$(INCLUDES) -L. $(MLX_LIB) -lXext -lX11 -lm -lz

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

c:	clean

f:	fclean

r:	re

.PHONY: all clean fclean re
