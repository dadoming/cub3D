# include "../includes/cub3D.h"

/**
 * -2 <- -1.2 |0| 1.2 -> 2
*/
double	excenter(double x)//TODO: maybe return int
{
	if (x >= 0)
		return (ceil(x));
	else
		return (floor(x));
}

float	XgridColl(t_game *game, double theta)
{
	t_vec2f	pos;
	char	chk;
	float	tofirstX;
	float	dist;


	pos.x = (int)(excenter(game->player.pos.x));
	tofirstX = pos.x - game->player.pos.x; //TODO: what if pos.x is less than game.x

	dist = fabs(tan(theta) * tofirstX / sin(theta)); // hypothenuse

	pos.y = game->player.pos.y + tan(theta) * tofirstX;

	while (1)
	{
		pos.x += excenter(cos(theta));
		pos.y += tan(theta) * excenter(cos(theta));
		
		chk = coordcheck(game, pos.x, pos.y);
		if (chk == '1' || chk == 0)
		{
			squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));				
			return dist;
		}

		// dist += sqrt(1 + tan(theta)*tan(theta));
		dist += fabs(tan(theta) / sin(theta));
		// squarecent_prop(game, pos, 2, rgbtocolor(128, 128, 0));
	}
	printf("Shouldn't get here\n");
}

float	YgridColl(t_game *game, double theta)
{
	t_vec2f	pos;
	char	chk;
	float	tofirstY;
	float	dist;


	pos.y = (int)(excenter(game->player.pos.y));
	// pos.y = (int)floor(game->player.pos.y);
	tofirstY = pos.y - game->player.pos.y;

	dist = fabs(tofirstY / tan(theta)); //TODO: can this be zero?

	pos.x = game->player.pos.x + tofirstY / tan(theta);

	while (1)
	{
		pos.y += excenter(sin(game->player.theta));
		pos.x += 1 / tan(theta) * excenter(sin(game->player.theta));

		chk = coordcheck(game, pos.x, pos.y);
		if (chk == '1' || chk == 0)
		{
			squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));
			return dist;
		}
		
		// dist += sqrt(1 + (1/tan(theta))*(1/tan(theta)));
		dist += fabs(1 / sin(theta));
		// squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));
	}
	printf("Shouldn't get here\n");
}

float	ray(t_game *game, double theta)
{
	t_vec2f	pos;
	char	chk;
	size_t	i;
	float	tox;
	float	toy;
	float	AB;

	pos.x = game->player.pos.x;
	pos.y = game->player.pos.y;

	AB = tan(theta);
	tox = AB / sin(theta);
	pos.x = excenter(pos.x);
	pos.y -= tox;
	squarecent_prop(game, pos, 4, rgbtocolor(50,50,50));


	// i = 0;
	// while (1)
	// {
	// 	chk = coordcheck(game, pos.x, pos.y);
	// 	if (chk == '1' || chk == 0)
	// 		return (i - 1) / 2;
	// 	squarecent_prop(game, pos, 4, rgbtocolor(50, 50, 50));
	// 	pos.x += cos(theta) / 2;
	// 	pos.y += sin(theta) / 2;
	// 	i++;
	// }
}

int	draw_ray(t_game *game)
{
	float	distx;
	float	disty;

	//TODO: negative dists returned!!!
	distx = XgridColl(game, game->player.theta);
	disty = YgridColl(game, game->player.theta);

	if (distx <= disty)
		printf("X is nearest: %f\n", distx);
	else
		printf("Y is nearest: %f\n", disty);

	// drawXgridColl(game);
	// drawYgridColl(game);
	// printf("%f\n", XgridColl(game, game->player.theta));
	// printf("%f\n", YgridColl(game, game->player.theta));
	// ray(game, game->player.theta);
	// printf("%f\n", ray(game, game->player.theta));
}