# include "../includes/cub3D.h"

int	prep_game(t_settings *setts)
{
	t_game	game;

	game.charmap = setts->charmap;

	game.mlx = mlx_init();
	if (!game.mlx)
		return 0; //TODO: gotta free and exit
    game.win = mlx_new_window(game.mlx, 800, 500, "cub3D");



	return (run_game(game));
	// return (1);
}