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

t_vec2f	ray(t_game *game, double theta)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		xstep;
	float	yatXintercept;
	float	yforXstep;
	int		ystep;
	float	xatYintercept;
	float	xforYstep;
	int		hit;
	int		side;

	x = (int)game->player.pos.x;
	y = (int)game->player.pos.y;

	dy = y + 1 - game->player.pos.y;
	dx = game->player.pos.x - x;

	xstep = excenter(cos(theta));
	yatXintercept = y + dy + dx * tan(theta);
	yforXstep = tan(theta) * xstep;

	ystep = excenter(sin(theta));
	xatYintercept = x + dx + (1 - dy) / tan(theta);
	xforYstep = 1 / tan(theta) * ystep;

	hit = 0;
	while (hit == 0)
	{
		if (x < xatYintercept)
		{
			x += xstep;
			yatXintercept += yforXstep;
			side = 0;
		}
		else
		{
			y += ystep;
			xatYintercept += xforYstep;			
			side = 1;
		}
		if (coordcheck(game, x, y) == '1')
			hit = 1;
	}
	return (vec2f(x, y));

	// while (yatXintercept > y)
	// {
	// 	if (coordcheck(game, x, yatXintercept) == '1' || coordcheck(game, x, yatXintercept) == 0)
	// 	{
	// 		// squarecent_prop(game, vec2f(xatYintercept, yatXintercept), 4, rgbtocolor(128,0,128));
	// 		return (vec2f(x, yatXintercept)); //TODO:
	// 	}
	// 	x += xstep; //TODO: 
	// 	yatXintercept += yforXstep;
	// }
	// while (xatYintercept < x)
	// {
	// 	if (coordcheck(game, xatYintercept, y) == '1' || coordcheck(game, xatYintercept, y) == 0)
	// 	{
	// 		// squarecent_prop(game, vec2f(xatYintercept, yatXintercept), 4, rgbtocolor(128,0,128));
	// 		return (vec2f(xatYintercept, y)); //TODO:
	// 	}
	// 	y += ystep;
	// 	xatYintercept += xforYstep;
	// }
}


int	draw_ray(t_game *game)
{
	// float	distx;
	// float	disty;
	// t_vec2f	x_pos;
	// t_vec2f	y_pos;
	t_vec2f		rayend;
	// x_pos = rayX(game, game->player.theta);
	// squarecent_prop(game, x_pos, 40, rgbtocolor(128,0,128));

	// y_pos = rayY(game, game->player.theta);
	// squarecent_prop(game, y_pos, 40, rgbtocolor(128,0,128));

	// if (distx <= disty)
	// 	printf("X is nearest: %f\n", distx);
	// else
	// 	printf("Y is nearest: %f\n", disty);

	// drawXgridColl(game);
	// drawYgridColl(game);
	// printf("%f\n", XgridColl(game, game->player.theta));
	// printf("%f\n", YgridColl(game, game->player.theta));
	rayend = ray(game, game->player.theta);
	square_propf(game, rayend, 1, rgbtocolor(128,0,128));

	// squarecent_prop(game, ray(game, game->player.theta), 4, rgbtocolor(128,0,128));
	// t_vec2f	pos;
	// pos.x = 65;
	// pos.y = 1;
	// squarecent_prop(game, pos, 4, rgbtocolor(128,0,128));
	// pos.x = 71;
	// pos.y = 15;
	// squarecent_prop(game, pos, 4, rgbtocolor(128,0,128));
	// printf("%f\n", ray(game, game->player.theta));
	return (1);
}