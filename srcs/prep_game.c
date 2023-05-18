# include "../includes/cub3D.h"

void free_objmap(char **map, t_object ***obj)
{
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == DOOR)
                free(obj[i][j]);
            else if (map[i][j] == WALL)
                free(obj[i][j]);
            j++;
        }
        free(obj[i]);
        i++;
    }
    free(obj);
}


void close_game(t_game *game)
{
    if (game->objmap)
        free_objmap(game->charmap, game->objmap);
    charmap_free(game->charmap);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->imgbuffer.img)
		mlx_destroy_image(game->mlx, game->imgbuffer.img);
	if (game->texture_wall.n.img)
		mlx_destroy_image(game->mlx, game->texture_wall.n.img);
	if (game->texture_wall.s.img)
		mlx_destroy_image(game->mlx, game->texture_wall.s.img);
	if (game->texture_wall.w.img)
		mlx_destroy_image(game->mlx, game->texture_wall.w.img);
	if (game->texture_wall.e.img)
		mlx_destroy_image(game->mlx, game->texture_wall.e.img);
    if (game->texture_door.img)
        mlx_destroy_image(game->mlx, game->texture_door.img);
    if (game->player_shoot.frames)
        free_anim_list(game, &game->player_shoot.frames);
    if (game->mlx)
		mlx_destroy_display(game->mlx);
    free(game->mlx);
    exit(0);
}

int x_close_window(t_game *game)
{
    close_game(game);
    return (0);
}

void load_pov(t_plinfo *player, float planeX, float planeY)
{
	player->planeX = planeX;
	player->planeY = planeY;
}

void load_orientation(t_plinfo *player, int dir_x, int dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

void define_start_orientation(t_plinfo *player)
{
	if (player->start == NORTH)
	{
		load_orientation(player, -1, 0);
		load_pov(player, 0, 0.66);
	}
	else if (player->start == SOUTH)
	{
		load_orientation(player, 1, 0);
		load_pov(player, 0, -0.66);
	}
	else if (player->start == EAST)
	{
		load_orientation(player, 0, 1);
		load_pov(player, 0.66, 0);
	}
	else if (player->start == WEST)
	{
		load_orientation(player, 0, -1);
		load_pov(player, -0.66, 0);
	}
}

t_object ***load_individual_map_tile(char **map, t_game *game)
{
	int i;
	int j;
	t_object ***obj;

	obj = ft_calloc(sizeof(t_object **), (ft_mtrxlen((void **)map) + 1));
	if (!obj)
		return (NULL);
	i = 0;
	j = 0;
	while (map[i])
	{
		obj[i] = ft_calloc(sizeof(t_object *), ft_strlen(map[i]) + 1);
		if (!obj[i])
			return (NULL);
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == DOOR)
				obj[i][j] = new_door(j, i, game);
			else if (map[i][j] == WALL)
				obj[i][j] = new_wall(game);
			else if (map[i][j] == STATICENEMY)
				obj[i][j] = new_staticenemy(game);
			j++;
		}
		i++;
	}
	return (obj);
}


int	prep_game(t_settings *map_settings, t_plinfo player, int mouse_selected)
{
	t_game	game;

	game.mlx = mlx_init();
	load_textures(&game, map_settings);
	
	game.charmap = map_settings->charmap;
    game.objmap = NULL;
	game.objmap = load_individual_map_tile(map_settings->charmap, &game);
	game.player = player;
  	define_start_orientation(&game.player);

	game.minimap_toggle = 0;
	game.mouse_selected = mouse_selected;

	// init mapsize
	game.mapsize.x = ft_strlen(game.charmap[0]);
	game.mapsize.y = ft_mtrxlen((void **)game.charmap);
	if (!game.mlx)
		close_game(&game);
    game.win = mlx_new_window(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y, "cub3D");
    


	game.imgbuffer.img = mlx_new_image(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
	game.imgbuffer.addr = mlx_get_data_addr(game.imgbuffer.img, &game.imgbuffer.bits_per_pixel, &game.imgbuffer.line_length, &game.imgbuffer.endian);
    if (!game.imgbuffer.img)
        close_game(&game);

    game.player.inv_pos.x = player.pos.x;
    game.player.inv_pos.y = player.pos.y;
    game.inv_mapsize.x = game.mapsize.y;
    game.inv_mapsize.y = game.mapsize.x;

	mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_event, &game);

	if (mouse_selected)
	{
		mlx_mouse_move(game.mlx, game.win, WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
		mlx_mouse_hide(game.mlx, game.win); // this gives mlx leaks
		mlx_hook(game.win, 6, 1L << 6, mousemove_capture, &game);
		mlx_hook(game.win, 4, 1L << 6, mousedown_capture, &game);
	}

	clock_gettime(CLOCK_MONOTONIC, &game.old_time);

	return (run_game(&game));
}
