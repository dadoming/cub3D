# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    charmapFree(game->charmap);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->imgbuffer.img)
		mlx_destroy_image(game->mlx, game->imgbuffer.img);
	if (game->texture.n.img)
		mlx_destroy_image(game->mlx, game->texture.n.img);
	if (game->texture.s.img)
		mlx_destroy_image(game->mlx, game->texture.s.img);
	if (game->texture.w.img)
		mlx_destroy_image(game->mlx, game->texture.w.img);
	if (game->texture.e.img)
		mlx_destroy_image(game->mlx, game->texture.e.img);
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

void load_orientation(t_plinfo *player, int dirX, int dirY)
{
	player->dirX = dirX;
	player->dirY = dirY;
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

t_object ***load_individual_map_tile(char **map)
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
				obj[i][j] = new_door(j, i);
			else if (map[i][j] == WALL)
				obj[i][j] = new_wall();
			j++;
		}
		i++;
	}
	return (obj);
}

int	prep_game(t_settings *map_settings, t_plinfo player)
{
	t_game	game;

	game.charmap = map_settings->charmap;
	game.objmap = load_individual_map_tile(map_settings->charmap);
	game.player = player;
  	define_start_orientation(&game.player);

	game.mlx = mlx_init();
	load_textures(&game, map_settings);
	game.minimap_toggle = 0;

	// init mapsize
	game.mapsize.x = ft_strlen(game.charmap[0]);
	game.mapsize.y = ft_mtrxlen((void **)game.charmap);
	if (!game.mlx)
		close_game(&game);
    game.win = mlx_new_window(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y, "cub3D");

	// Setup ImageBuffer
	game.imgbuffer.img = mlx_new_image(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
	game.imgbuffer.addr = mlx_get_data_addr(game.imgbuffer.img, &game.imgbuffer.bits_per_pixel, &game.imgbuffer.line_length, &game.imgbuffer.endian);
    
    game.player.inv_pos.x = player.pos.x;
    game.player.inv_pos.y = player.pos.y;
    game.inv_mapsize.x = game.mapsize.y;
    game.inv_mapsize.y = game.mapsize.x;
	
	// game.player.dirX = -1;
	// game.player.dirY = 0;
    // game.player.planeX = 0;
    // game.player.planeY = 0.66;

	mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_event, &game);
	
	return (run_game(&game));
}
