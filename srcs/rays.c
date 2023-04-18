# include "../includes/cub3D.h"

/**
 * -2 <- 1.2 || 1.2 -> 2
*/
double	excenter(double x)
{
	if (x >= 0)
		return (ceil(x));
	else
		return (floor(x));
}

void	drawXgridColl(t_game *game)
{
	t_vec2f	pos;
	float		base;
	char	chk;
	size_t	i;

	pos.x = (int)(game->player.pos.x * excenter(cos(game->player.pos.x)))

	i = 1;
	while (i)
	{
		// base = (excenter(game->player.pos.x) - game->player.pos.x) * i;
		pos.x += excenter(cos(game->player.pos.x));
		pos.y = game->player.pos.y + tan(game->player.theta) * base;// * excenter(cos(game->player.theta));
		pos.y = roun

		chk = coordcheck(game, pos.x, pos.y);
		if (chk == '1' || chk == 0)
			return;
		squarecent_prop(game, pos, 4, rgbtocolor(128, 0, 128));
		i++;
	}
	printf("Shouldn't get here\n");
}

int	draw_ray(t_game *game)
{
	drawXgridColl(game);
}