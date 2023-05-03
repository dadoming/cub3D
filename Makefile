NAME = cub3D

LIBFT_DIRECTORY = libft/
LIBFT_HEADER = $(LIBFT_DIRECTORY)libft.h
LIBFT = $(LIBFT_DIRECTORY)libft.a

MLX_DIRECTORY = minilibx-linux/
MLX_HEADER = $(MLX_DIRECTORY)mlx.h
MLX = $(MLX_DIRECTORY)libmlx.a

HEADERS_LIST = cub3D.h
HEADERS_DIRECTORY = includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

TEXTURES_LIST = load_textures.c rgb_convert.c
TEXTURES_DIRECTORY = textures/
TEXTURES = $(addprefix $(TEXTURES_DIRECTORY), $(TEXTURES_LIST))

MAP_LIST = checksettings.c filextract.c initmapsettings.c player_orientation.c readsettings.c create_borders.c get_map_sizes.c invalid_chars.c preparemap.c residualcleaning.c
MAP_DIRECTORY = map/
MAP = $(addprefix $(MAP_DIRECTORY), $(MAP_LIST))

SRCS_LIST = $(MAP) $(TEXTURES) main.c check_input.c color.c draw.c imgbuffer.c line.c movement.c prep_game.c rays.c run_game.c square.c vector.c door.c wall.c minimap.c crosshair.c
SRCS_DIRECTORY = srcs/
SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJECT_LIST = $(SRCS_LIST:.c=.o)
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

CC = cc
CFLAGS = -g3 -Wall -Wextra #-fsanitize=address #-Werror

LIBS = -L$(LIBFT_DIRECTORY) -lft $(MLX) -lXext -lX11 -lm -lz
INCLUDES = -I.$(HEADERS) -I.$(LIBFT_HEADER) -I.$(MLX_HEADER)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(MAP_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(TEXTURES_DIRECTORY)


$(OBJECTS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT):
	make -sC $(LIBFT_DIRECTORY) --no-print-directory

$(MLX):
	cd $(MLX_DIRECTORY) && ./configure 

clean: 
	rm -rf $(OBJECTS_DIRECTORY)
	make -sC $(LIBFT_DIRECTORY) clean --no-print-directory

fclean: clean
	rm -rf $(NAME)
	make -sC $(LIBFT_DIRECTORY) fclean --no-print-directory
	rm -rf $(MLX)

re: fclean $(NAME)


c:	clean

f:	fclean

r:	clean all
	./cub3D

.PHONY: all clean fclean re