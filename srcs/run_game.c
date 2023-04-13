# include "../includes/cub3D.h"

int	theloop(t_game *game)
{
	// static size_t	frame = 0;

	// if (frame == 6000)
	// {
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
		pixsquarecent(game, game->player.pos, 50, rgbtocolor(0, 255, 0));
		line_tf(game, game->player.pos, 150, rgbtocolor(255, 50, 50));
		line_tf(game, game->player.pos, 150, rgbtocolor(255, 50, 50));

	// 	frame = 0;
	// }
	// frame++;
}


int run_game(t_game *game)
{
	t_vec2i	vec1;
	t_vec2i	vec2;

	game->player.theta = M_PI;

	game->player.pos.x = 150;
	game->player.pos.y = 150;




	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}