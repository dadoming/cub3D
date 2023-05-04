# include "../includes/cub3D.h"

void draw_floor_and_sky(t_game *game)
{
	int x = 0;
	int y = 0;
	while (x < WINDOWSIZE_X)
	{
		y = 0;
		while (y < WINDOWSIZE_Y / 2)
		{
			mypixelput(&game->imgbuffer, x, y, rgbtocolor(48, 138, 228));
			y++;
		}
		x++;
	}
	x = 0;
	while (x < WINDOWSIZE_X)
	{
		y = WINDOWSIZE_Y / 2;
		while (y < WINDOWSIZE_Y)
		{
			mypixelput(&game->imgbuffer, x, y, rgbtocolor(9, 112, 12));
			y++;
		}
		x++;
	}
}

int	theloop(t_game *game)
{
    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;
	myclearimg(game);
	draw_floor_and_sky(game);
	draw_ray(game);
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
    return (0);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}