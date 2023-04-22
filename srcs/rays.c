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


	tmp.x = (int)(excenter(px));
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
	double ra;
	float rx, ry, xoffset, yoffset;
	int	r, mx, my, mp, dof;
	float aTan;

	ra = theta;

	// dof = 0;
	// aTan = 1 / tan(ra);


	// HORIZONTAL LINES
	if (ra == 0 || ra == M_PI)
	{
		rx = px;
		ry = py;
		// dof = 8;
		return (vec2f(rx, ry));
	}
	else if (ra < M_PI) // if looking upwards
	{
		ry = (int)py;// - 0.0001f; // subtraction is important!
		rx = px + (py - ry) / tan(ra);
		yoffset = -1;
		xoffset = 1 / tan(ra);
	}
	else // if (ra > M_PI)// looking downwards
	{
		ry = ceil(py);// + 0.0001f;
		rx = px + (ry - py) / tan(ra);
		yoffset = 1;
		xoffset = -1 / tan(ra);
	}
	
	// while (dof < 8)
	while (1)
	{
		mx = (int)(rx / 64) *64;
		my = (int)(ry / 64) *64;
		// if (coordcheck_prop(game, mx, my) == '1' || coordcheck_prop(game, mx, my) == 0)
		if (coordcheck(game, mx, my) == '1' || coordcheck(game, mx, my) == 0)
			return (vec2f(rx, ry));
			// dof = 8;
		else
		{
			rx += xoffset;
			ry += yoffset;
			// dof++;
		}
	}
	// square_propf(game, vec2f(rx, ry), 1, rgbtocolor(128,0,128));
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
	// square_propf(game, rayend, 1, rgbtocolor(128,0,128));
	line_odprop(game, ppos, rayend, rgbtocolor(0,255,0));
	line(game, vec2i(px, py), vec2i(rayend.x, rayend.y), rgbtocolor(0,255,0));
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