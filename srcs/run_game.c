# include "../includes/cub3D.h"

int	theloop(t_game *game)
{
    struct timespec now;
    microSeconds delta;

	clock_gettime(CLOCK_MONOTONIC, &now);

    delta = timestampdiff(now, game->old_time);
    if (delta < 17000) // 60fps
        return (0);

    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;

	myclearimg(game);
	draw_ray(game);
    update(game, timestamp(now));
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);

    clock_gettime(CLOCK_MONOTONIC, &game->old_time);
    return (1);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}