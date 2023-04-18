# include "../includes/cub3D.h"

/**
 * -2 <- 1.2 || 1.2 -> 2
*/
double	excenter(double x)//TODO: maybe return int
{
	if (x >= 0)
		return (ceil(x));
	else
		return (floor(x));
}

void	drawXgridColl(t_game *game)
{
	t_vec2f	pos;
	char	chk;

	pos.x = (int)(excenter(game->player.pos.x));
	pos.y = game->player.pos.y + tan(game->player.theta) * (pos.x - game->player.pos.x);//TODO: what if pos.x is less than game.x

	while (1)
	{
		pos.x += excenter(cos(game->player.theta));
		pos.y = game->player.pos.y + tan(game->player.theta) * (pos.x - game->player.pos.x);

		chk = coordcheck(game, pos.x, pos.y);
		if (chk == '1' || chk == 0)
			return;
		squarecent_prop(game, pos, 2, rgbtocolor(128, 128, 0));
	}
	printf("Shouldn't get here\n");
}

void	drawYgridColl(t_game *game)
{
	t_vec2f	pos;
	char	chk;

	pos.y = (int)(excenter(game->player.pos.y));
	pos.x = game->player.pos.x + (pos.y - game->player.pos.y) / tan(game->player.theta);//TODO: what if pos.y is less than game.y

	while (1)
	{
		pos.y += excenter(sin(game->player.theta));
		pos.x = game->player.pos.x + (pos.y - game->player.pos.y) / tan(game->player.theta);//TODO: what if pos.y is less than game.y

		chk = coordcheck(game, pos.x, pos.y);
		if (chk == '1' || chk == 0)
			return;
		squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));
	}
	printf("Shouldn't get here\n");
}

int	draw_ray(t_game *game)
{
	drawXgridColl(game);
	drawYgridColl(game);
}