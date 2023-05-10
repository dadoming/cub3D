# include "../includes/cub3D.h"

int	mousemove_capture(int x, int y, void *param)
{
	static int oldx = 0;
	// static int oldy = 0;
	t_game *game;

	game = param;
	printf("%d__%d\n", x, y);

	if (x > oldx)
		rotate_direction(game, cos(-ROTATESPEED), sin(-ROTATESPEED));
	if (x < oldx)
		rotate_direction(game, cos(ROTATESPEED), sin(ROTATESPEED));
	oldx = x;
	// oldy = y;
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
	(void)x;
	(void)y;
	return (1);
}