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
	t_vec2f	tmp;
	t_vec2f	pos;
	char	chk;
	float	tofirstX;
	float	dist;


	tmp.x = (int)(excenter(game->player.pos.x));
	tofirstX = tmp.x - game->player.pos.x; //TODO: what if pos.x is less than game.x

	dist = fabs(tan(theta) * tofirstX / sin(theta)); // hypothenuse

	tmp.y = game->player.pos.y + tan(theta) * tofirstX;

	pos.x = tmp.x;
	pos.y = tmp.y;
	while (1)
	{
		tmp.x += excenter(cos(theta));
		tmp.y += tan(theta) * excenter(cos(theta));

		chk = coordcheck(game, tmp.x, tmp.y);
		if (chk == '1' || chk == 0)
		{
			squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));				
			return dist;
		}
		pos.x = tmp.x;
		pos.y = tmp.y;

		// dist += sqrt(1 + tan(theta)*tan(theta));
		// dist += fabs(tan(theta) / sin(theta));
		dist += fabs(1 / cos(theta));
		// squarecent_prop(game, pos, 2, rgbtocolor(128, 128, 0));
	}
	printf("Shouldn't get here\n");
}

float	YgridColl(t_game *game, double theta)
{
	t_vec2f	tmp;
	t_vec2f	pos;
	char	chk;
	float	tofirstY;
	float	dist;


	tmp.y = (int)(excenter(game->player.pos.y));
	// pos.y = (int)floor(game->player.pos.y);
	tofirstY = tmp.y - game->player.pos.y;

	dist = fabs(tofirstY / tan(theta)); //TODO: can this be zero?

	tmp.x = game->player.pos.x + tofirstY / tan(theta);

	pos.x = tmp.x;
	pos.y = tmp.y;

	while (1)
	{
		tmp.y += excenter(sin(game->player.theta));
		tmp.x += 1 / tan(theta) * excenter(sin(game->player.theta));

		chk = coordcheck(game, tmp.x, tmp.y);
		if (chk == '1' || chk == 0)
		{
			squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));
			return dist;
		}
		pos.x = tmp.x;
		pos.y = tmp.y;

		// dist += sqrt(1 + (1/tan(theta))*(1/tan(theta)));
		dist += fabs(1 / sin(theta));
		// squarecent_prop(game, pos, 2, rgbtocolor(128, 0, 128));
	}
	printf("Shouldn't get here\n");
}

float	ray(t_game *game, double theta)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	xatYintercept;
	float	yatXintercept;
	float	yforXstep;
	float	xforYstep;

	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;

	dy = game->player.pos.y - y;
	dx = game->player.pos.x - x;

	xatYintercept = x + dx + dy / tan(theta);
	xforYstep = 1 / tan(theta);

	yatXintercept = y + dy + dx * tan(theta);
	yforXstep = tan(theta);

	x = x * 1;
	while (1)
	{
		if (coordcheck(game, x, (int)yatXintercept) == '1' || coordcheck(game, x, yatXintercept) == 0)
		{
			squarecent_prop(game, )
			break ; //TODO:
		}
		x += 1; //TODO: 
		yatXintercept += yforXstep;
	}
}

int	draw_ray(t_game *game)
{
	// float	distx;
	// float	disty;

	//TODO: negative dists returned!!!
	// distx = XgridColl(game, game->player.theta);
	// disty = YgridColl(game, game->player.theta);

	// if (distx <= disty)
	// 	printf("X is nearest: %f\n", distx);
	// else
	// 	printf("Y is nearest: %f\n", disty);

	// drawXgridColl(game);
	// drawYgridColl(game);
	// printf("%f\n", XgridColl(game, game->player.theta));
	// printf("%f\n", YgridColl(game, game->player.theta));
	ray(game, game->player.theta);
	printf("%f\n", ray(game, game->player.theta));
}