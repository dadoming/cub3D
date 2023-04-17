# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
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
        close_game(game);
		printf("ESC\n");
		// printf("%i\n", (int)(1.5f - 0.3f));
	}
	else if (key == A)
	{
		game->player.theta -= M_PI / RADJUMP;
	}
	else if (key == D)
	{
		game->player.theta += M_PI / RADJUMP;
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

int	prep_game(t_settings *map_settings, t_plinfo player)
{
	t_game	game;

	// texture init
	//if (load_textures(&game, map_settings))
	//{
	//	free_on_invalid(map_settings);
	//}
	game.player = player;
	game.charmap = map_settings->charmap;
  
	//David esta a implementar
	game.player.pos.x = 5;
	game.player.pos.y = 4;
	game.player.theta = M_PI * 1.5f;
	// _

	game.mlx = mlx_init();
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