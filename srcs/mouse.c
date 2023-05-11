# include "../includes/cub3D.h"

int	mousemove_capture(int x, int y, void *param)
{
	static int oldx = 0;
	t_game *game;

	game = param;
	printf("%d__%d\n", x, y);

	if (x > oldx)
		rotate_direction(game, cos(-ROTATESPEED/8), sin(-ROTATESPEED/8));
	if (x < oldx)
		rotate_direction(game, cos(ROTATESPEED/8), sin(ROTATESPEED/8));
	oldx = x;
	(void)param;
	return (1);
}

int	mousedown_capture(int button, int x, int y, void *param)
{
	t_game *game;

	printf("Button: %d\n", button);
	game = param;
	if (button == 1)
		animate(&game->player_animation);
	else if (button == 3)
	{
		if (game->select && game->select->action)
			game->select->action(game->select, game);
	}
	else if (button == 4)
		game->minimap_toggle = 0;
	else if (button == 5)
		game->minimap_toggle = 1;
	(void)x;
	(void)y;
	return (1);
}