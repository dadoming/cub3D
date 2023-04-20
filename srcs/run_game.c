# include "../includes/cub3D.h"

int	theloop(t_game *game)
{
	// static size_t	frame = 0;

	// if (frame == 10000)
	// {
		//TODO: implement my clear image
		//TODO: Here is where we insuflate the proportions
		myclearimg(game);
		// draw_map(game);
		draw_player(game);
		// draw_ray(game);
		mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
	// 	frame = 0;
	// }
	// frame++;
}


int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}