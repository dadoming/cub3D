# include "../includes/cub3D.h"

void update(t_game *game)
{
	if (game->minimap_toggle == 0)
		draw_minimap(game);
    update_gun(game);
    draw_weapon(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
}

int	theloop(t_game *game)
{
    if (timediff(game->old_time) < 34) // 30fps
        return (0);

    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;

	myclearimg(game);
	draw_ray(game);
    update(game);
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);

    gettimeofday(&game->old_time, NULL);
    return (1);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}