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
		printf("%i\n", (int)(1.5f - 0.3f));
	}
    return (0);
}

int	theloop(t_game *game)
{
	// static int	frame = 0;

	// if (frame == 1600)
	// {
		// draw_map(game);
	// 	frame = 0;
	// }
	// frame++;
	// return (frame);
	// mlx_pixel_put(game->mlx, game->win, 50, 50, rgbtocolor(128, 128, 128));
}


int	pixsquare(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pos.y += 1;
		horline(game, pos, size, color);
		i++;
	}
	return (1);

}

#define SQUARESIZE 5
int	draw_map(t_game *game)
{
	size_t	j;
	size_t	i;
	t_vec2i	vec;
	
	j = 0;
	vec.y = 50;
	while (game->charmap[j] != NULL)
	{
		i = 0;
		vec.x = 50;
		while (game->charmap[j][i] != '\0')
		{
			if (game->charmap[j][i] == '1')
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(23, 128, 250));
			else if (game->charmap[j][i] == '0')
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(23, 128, 20));
			else if (ft_charinside(game->charmap[j][i], "NSWE"))
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(255, 0, 0));
			
			vec.x += SQUARESIZE;
			i++;
		}
		vec.y += SQUARESIZE;
		j++;
	}
	return (1);
}

int run_game(t_game game)
{

	t_vec2i	vec1;
	t_vec2i	vec2;

	vec1.x = 50;
	vec1.y = 50;
	vec2.x = 200;
	vec2.y	= 328;
	// square(&game, vec, 50, rgbtocolor(23, 128, 128));

	// draw_map(&game);
	line(&game, vec1, vec2, rgbtocolor(255, 50, 100));
	pixsquare(&game, vec1, 10, rgbtocolor(0, 255, 0));
	pixsquare(&game, vec2, 10, rgbtocolor(0, 255, 0));
	
    mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
    mlx_hook(game.win, 2, 1L<<0, key_event, &game);
	// mlx_loop_hook(game.mlx, theloop, &game);
    mlx_loop(game.mlx);
	
	return (1);
}