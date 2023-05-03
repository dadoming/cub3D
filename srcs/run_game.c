# include "../includes/cub3D.h"

int	theloop(t_game *game)
{
    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;
	myclearimg(game);
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