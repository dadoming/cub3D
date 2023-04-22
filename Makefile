# configure -> libmlx_Linux.a 

NAME	= cub3D

# SRCS = srcs/main.c srcs/check_input.c srcs/run_game.c
SRCS	= $(wildcard srcs/*.c) $(wildcard srcs/map/*.c) $(wildcard srcs/textures/*.c)

OBJS	= $(SRCS:.c=.o)

INCLUDES	= includes/cub3D.h libft/libft.h

CC	= cc

CFLAGS	= -fPIE -g3 -Wall -Wextra -Iincludes -Ilibft #-fsanitize=address #-Werror   

MLX_LIB	= minilibx-linux/libmlx.a

LIBFT	= libft/libft.a

all: $(MLX_LIB) $(LIBFT) $(NAME)

$(MLX_LIB):
	cd minilibx-linux && ./configure

$(LIBFT):
	make -C libft re
	make -C libft clean

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. $(MLX_LIB) $(LIBFT) -lXext -lX11 -lm -lz -fPIE

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT) # $(MLX_LIB) 

re: fclean all

c:	clean

f:	fclean

r:	clean all

.PHONY: all clean fclean re
