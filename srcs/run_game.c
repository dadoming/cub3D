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

#define RADJUMP 16

int key_event(int key, t_game *game)
{
    //printf("key> %d\n", key);
    if (key == ESC)
	{
        close_game(game);
		printf("ESC\n");
		printf("%i\n", (int)(1.5f - 0.3f));
	}
	else if (key == A)
	{
		game->player.theta -= M_PI / RADJUMP;
		// game->player.theta -= M_PI_4;
	}
	else if (key == D)
	{
		game->player.theta += M_PI / RADJUMP;
		// game->player.theta += M_PI_4;
	}
	else if (key == W)
	{
		//TODO: implement posoffset
		game->player.pos.x += cos(game->player.theta) * RADJUMP;
		game->player.pos.y += sin(game->player.theta) * RADJUMP;
	}
	else if (key == S)
	{
		// game->player.direction.y += +0.1f;
	}
    return (0);
}

int	theloop(t_game *game)
{
	static size_t	frame = 0;

	if (frame == 6000)
	{
		mlx_clear_window(game->mlx, game->win);
		// draw_map(game);
		pixsquare(game, game->player.pos, 10, rgbtocolor(0, 255, 0));
		line_t(game, game->player.pos, 100, rgbtocolor(255, 50, 100));
		frame = 0;
	}
	frame++;
}


int run_game(t_game *game)
{
	t_vec2i	vec1;
	t_vec2i	vec2;

	game->player.theta = -9 * M_PI / RADJUMP;

	game->player.pos.x = 150;
	game->player.pos.y = 150;
	vec2.x = 200;
	vec2.y	= 328;
	// square(game, vec, 50, rgbtocolor(23, 128, 128));

	draw_map(game);
	// line_s(game, game->player.pos, 100, rgbtocolor(255, 50, 100));
	pixsquare(game, game->player.pos, 10, rgbtocolor(0, 255, 0));
	pixsquare(game, vec2, 10, rgbtocolor(0, 255, 0));
	
    mlx_hook(game->win, 17, 1L<<2, x_close_window, game);
    mlx_hook(game->win, 2, 1L<<0, key_event, game);
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	
	return (1);
}