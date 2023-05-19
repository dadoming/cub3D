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

TEXTURES_LIST = load_textures.c rgb_convert.c rgb_norm.c
TEXTURES_DIRECTORY = textures/
TEXTURES = $(addprefix $(TEXTURES_DIRECTORY), $(TEXTURES_LIST))

MAP_LIST = checksettings.c filextract.c initmapsettings.c player_orientation.c player_orientation2.c readsettings.c create_borders.c get_map_sizes.c invalid_chars.c preparemap.c residualcleaning.c free_on_invalid.c
MAP_DIRECTORY = map/
MAP = $(addprefix $(MAP_DIRECTORY), $(MAP_LIST))

RAYCAST_LIST = raycast.c draw_texture.c line_height.c ray_calculation.c
RAYCAST_DIRECTORY = raycaster/
RAYCAST = $(addprefix $(RAYCAST_DIRECTORY), $(RAYCAST_LIST))

MENU_LIST = map_menu.c mlx_event.c circular_ll.c get_maps.c loop_utils.c draw_menu.c
MENU_DIRECTORY = menu/
MENU = $(addprefix $(MENU_DIRECTORY), $(MENU_LIST))

ANIMATIONS_LIST = anim_list.c
ANIMATIONS_DIRECTORY = animations/
ANIMATIONS = $(addprefix $(ANIMATIONS_DIRECTORY), $(ANIMATIONS_LIST))

SRCS_LIST = $(MAP) $(TEXTURES) $(RAYCAST) $(MENU) $(ANIMATIONS) main.c color.c draw.c imgbuffer.c line.c movement.c prep_game.c run_game.c square.c vector.c door.c wall.c minimap.c crosshair.c mouse.c time.c gun.c update.c capybara.c object.c staticenemy.c init_player_start.c keys.c coordcheck.c
SRCS_DIRECTORY = srcs/
SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJECT_LIST = $(SRCS_LIST:.c=.o)
OBJECTS_DIRECTORY = objects/
OBJECTS = $(addprefix $(OBJECTS_DIRECTORY), $(OBJECT_LIST))

CC = cc
CFLAGS = -g3 -Wall -Werror -Wextra #-fsanitize=address 

LIBS = -L$(LIBFT_DIRECTORY) -lft $(MLX) -lXext -lX11 -lm -lz
INCLUDES = -I.$(HEADERS) -I.$(LIBFT_HEADER) -I.$(MLX_HEADER)

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) $(LIBS) -o $(NAME)

$(OBJECTS_DIRECTORY):
	mkdir -p $(OBJECTS_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(MAP_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(TEXTURES_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(RAYCAST_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(MENU_DIRECTORY)
	mkdir -p $(OBJECTS_DIRECTORY)$(ANIMATIONS_DIRECTORY)

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
	# ./cub3D

.PHONY: all clean fclean re