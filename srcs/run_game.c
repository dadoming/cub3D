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
        // close_game(game);
		printf("hello\n");

	}
    return (0);
}

static void	intbin_append(int *color, unsigned char fam)
{
	*color = *color << 8;
	*color = *color | fam;
}

int	rgbtocolor(unsigned char r, unsigned char g, unsigned char b)
{
	int		color;

	color = 127;
	intbin_append(&color, r);
	intbin_append(&color, g);
	intbin_append(&color, b);
	return (color);
}

int	draw_map(t_game *game)
{
	size_t	j;
	size_t	i;

	mlx_clear_window(game->mlx, game->win);
	j = 0;
	while (game->charmap[j] != NULL)
	{
		mlx_string_put(game->mlx, game->win, 50, (j+20)*10, rgbtocolor(128, 33, 45), game->charmap[j]);

		// i = 0;
		// while (game->charmap[j][i] != '\0')
		// {
		// 	// draw_core(game, i, j);
		// 	i++;
		// }
		j++;
	}

	return (1);
}

int	theloop(t_game *game)
{
	static int	frame = 0;

	// if (frame == 1600)
	// {
		draw_map(game);
	// 	frame = 0;
	// }
	// frame++;
	return (frame);
}

int run_game(t_game game)
{
    mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
    mlx_hook(game.win, 2, 1L<<0, key_event, &game);
	mlx_loop_hook(game.mlx, theloop, &game);
    mlx_loop(game.mlx);
	
	return (1);
}