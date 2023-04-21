# include "../includes/cub3D.h"

int	theloop(t_game *game)
{
		myclearimg(game);
		draw_map(game);
		draw_player(game);
		// // draw_ray(game);
		pixsquare(game, vec2i(px, py), 10, rgbtocolor(128,20,100));
		mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);

}


int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}