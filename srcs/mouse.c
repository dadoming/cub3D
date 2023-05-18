# include "../includes/cub3D.h"

# define DEADZONE 370
# define ROTDIVIDER 8
int	mousemove_capture(int x, int y, void *param)
{
	// static int oldx = 0;
	t_game *game;
	int distance;

	game = param;
	// distance = sqrt(x * x + y * y);
	// if (distance <= DEADZONE)
	// 	return (1);
	if (x > WINDOWSIZE_X / 2)
		rotate_direction(game, cos(-ROTATESPEED/ROTDIVIDER), sin(-ROTATESPEED/ROTDIVIDER));
	if (x < WINDOWSIZE_X / 2)
		rotate_direction(game, cos(ROTATESPEED/ROTDIVIDER), sin(ROTATESPEED/ROTDIVIDER));
	// oldx = x;
	mlx_mouse_move(game->mlx, game->win, WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
	return (1);
}

int	mousedown_capture(int button, int x, int y, void *param)
{
	t_game *game;

	game = param;
	if (button == 1)
		game->player_shoot.trigger = 1;
	else if (button == 3)
	{
		if ((*(game->select)) && (*(game->select))->action)
			(*(game->select))->action(game->select, game);
	}
	else if (button == 4)
		game->minimap_toggle = 0;
	else if (button == 5)
		game->minimap_toggle = 1;
	(void)x;
	(void)y;
	return (1);
}