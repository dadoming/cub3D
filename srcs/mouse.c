# include "../includes/cub3D.h"

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