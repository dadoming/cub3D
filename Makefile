# configure -> libmlx_Linux.a 

NAME = cub3D

SRCS = srcs/main.c srcs/check_input.c srcs/run_game.c

OBJS = $(SRCS:.c=.o)

INCLUDES = includes/cub3D.h

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX_LIB = minilibx-linux/libmlx_Linux.a

RM = rm -f

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	cd minilibx-linux && ./configure

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) -L. $(MLX_LIB) -lXext -lX11 -lm -lz 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
