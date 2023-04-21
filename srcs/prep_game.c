# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    charmapFree(game->charmap);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_image(game->mlx, game->imgbuffer.img);
	mlx_destroy_image(game->mlx, game->texture.n.ptr);
	mlx_destroy_image(game->mlx, game->texture.s.ptr);
	mlx_destroy_image(game->mlx, game->texture.w.ptr);
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

int key_event(int key, t_game *game)
{
    //printf("key> %d\n", key);
    if (key == ESC)
	{
		printf("ESC\n");
        close_game(game);
		// printf("%i\n", (int)(1.5f - 0.3f));
	}
	else if (key == A)
	{
		game->player.theta -= M_PI / RADJUMP;
		printf("%f\n", game->player.theta);
	}
	else if (key == D)
	{
		game->player.theta += M_PI / RADJUMP;
		printf("%f\n", game->player.theta);
	}
	else if (key == W)
	{
		p_move(game, 1, 1);
	}
	else if (key == S)
	{
		p_move(game, -1, -1);
	}
    return (0);
}

void define_start_orientation(t_plinfo *player)
{
	if (player->theta == NORTH)
		player->theta = M_PI * 1.5f;
	else if (player->theta == 'S')
		player->theta = M_PI * 0.5f;
	else if (player->theta == 'E')
		player->theta = 0;
	else if (player->theta == 'W')
		player->theta = M_PI;
}

int	prep_game(t_settings *map_settings, t_plinfo player)
{
	t_game	game;


	game.player.pos.x = 7.3f;
	game.player.pos.y = 5.6f;
	// game.player.theta = M_PI * 1.3203f;
	game.player.theta = 5.9149905948490558f;
	game.charmap = map_settings->charmap;

	//game.player = player;
  //define_start_orientation(&game.player);

	game.mlx = mlx_init();
	load_textures(&game, map_settings);
	if (!game.mlx)
		return 0; //TODO: gotta free and exit
    game.win = mlx_new_window(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y, "cub3D");

	// Setup ImageBuffer
	game.imgbuffer.img = mlx_new_image(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
	game.imgbuffer.addr = mlx_get_data_addr(game.imgbuffer.img, &game.imgbuffer.bits_per_pixel, &game.imgbuffer.line_length, &game.imgbuffer.endian);

	mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
	mlx_hook(game.win, 2, 1L<<0, key_event, &game);
	
	return (run_game(&game));
	// return (1);
}