# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    charmapFree(game->charmap);
	if (game->door)
		free(game->door);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->imgbuffer.img)
		mlx_destroy_image(game->mlx, game->imgbuffer.img);
	if (game->texture.n.ptr)
		mlx_destroy_image(game->mlx, game->texture.n.ptr);
	if (game->texture.s.ptr)
		mlx_destroy_image(game->mlx, game->texture.s.ptr);
	if (game->texture.w.ptr)
		mlx_destroy_image(game->mlx, game->texture.w.ptr);
	if (game->texture.e.ptr)
		mlx_destroy_image(game->mlx, game->texture.e.ptr);
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

void define_start_orientation(t_plinfo *player)
{
	if (player->theta == NORTH)
		player->theta = M_PI * 0.5f;
	else if (player->theta == SOUTH)
		player->theta = M_PI * 1.5f;
	else if (player->theta == EAST)
		player->theta = 0;
	else if (player->theta == WEST)
		player->theta = M_PI;
}

int	prep_game(t_settings *map_settings, t_plinfo player)
{
	t_game	game;

	game.charmap = map_settings->charmap;
	game.player = player;
  	define_start_orientation(&game.player);

	game.mlx = mlx_init();
	load_textures(&game, map_settings);
	init_doors(&game);
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
    game.player.dirX = -1;
    game.player.dirY = 0;
    game.player.planeX = 0;
    game.player.planeY = 0.66;


	mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_event, &game);
	
	return (run_game(&game));
}
