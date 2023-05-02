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

t_vec2f	rayHor(t_game *game, double theta)
{
	float rx, ry, xoffset, yoffset;
	int	mx, my;

	// HORIZONTAL LINES
	if (theta == 0 || theta == M_PI)
	{
		return (vec2f(px, py));
	}
	else if (theta < M_PI) // if looking upwards
	{
		ry = (int)py;// - 0.0001f; // subtraction is important!
		rx = px + (py - ry) / tan(theta);
		yoffset = -1;
		xoffset = 1 / tan(theta);
	}
	else // if (theta > M_PI)// looking downwards
	{
		ry = ceil(py);// + 0.0001f;
		rx = px + (ry - py) / tan(theta);
		yoffset = 1;
		xoffset = -1 / tan(theta);
	}
	
	while (1)
	{
		mx = (int)(rx / 64);
		my = (int)(ry / 64);
		if (coordcheck(game, mx, my) == '1' || coordcheck(game, mx, my) == 0)
			return (vec2f(rx, ry));
		else
		{
			rx += xoffset;
			ry += yoffset;
		}
	}
}

t_vec2f	rayVer(t_game *game, double theta)
{
	float rx, ry, xoffset, yoffset;
	int	mx, my;

	// VERTICAL LINES
	if (theta == M_PI_2 || theta == 3 * M_PI_2)
	{
		return (vec2f(px, py));
	}
	else if (theta < M_PI_2 || theta > 3 * M_PI_2) // if looking right
	{
		rx = ceil(px);
		ry = py + (rx - px) * -tan(theta);
		xoffset = 1;
		yoffset = -tan(theta);
	}
	else // if (theta > M_PI || theta < 3 * M_PI / 2) // looking left
	{
		rx = (int)px;
		ry = py + (px - rx) * tan(theta);
		xoffset = -1;
		yoffset = tan(theta);
	}
	
	while (1)
	{
		mx = (int)(rx / 64);
		my = (int)(ry / 64);
		if (coordcheck(game, mx, my) == '1' || coordcheck(game, mx, my) == 0)
			return (vec2f(rx, ry));
		else
		{
			rx += xoffset;
			ry += yoffset;
		}
	}
}

t_vec2f	ray(t_game *game, double theta)
{
	t_vec2f	hor;
	t_vec2f	vert;

	if (theta < 0)
		theta += 2*M_PI;
	if (theta > 2*M_PI)
		theta -= 2*M_PI;
	hor = rayHor(game, theta);
	vert = rayVer(game, theta);
	return (vec2f(vert.x, hor.y));
}


int	draw_ray(t_game *game)
{
	// float	distx;
	// float	disty;
	// t_vec2f	x_pos;
	// t_vec2f	y_pos;
	t_vec2f		rayend;

	rayend = ray(game, pt);
	line(game, vec2i(px, py), vec2i(rayend.x, rayend.y), rgbtocolor(0,255,0));
	return (1);
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
	// square_propf(game, rayend, 1, rgbtocolor(128,0,128));
	// line_odprop(game, ppos, rayend, rgbtocolor(0,255,0));
	
	
	// sixty deg is M_PI / 3 and is divided by 2 because we want 
	//  to display rays from the half of the negative to half of the positive
	float final_distance;
	float sixty_degrees = (M_PI / 3) / 2;  
	float i = -1 * sixty_degrees;
	while (i < sixty_degrees)
	{
		rayend = ray(game, game->player.theta + i);
		line(game, vec2i(px, py), vec2i(rayend.x, rayend.y), rgbtocolor(0,255,0));

		if (rayend.x > rayend.y)
		{
			final_distance = rayend.y;
		}

		if (rayend.x < rayend.y)
		{
			final_distance = rayend.x;
		}

		int line_height = WINDOWSIZE_Y / final_distance;
		if (line_height > WINDOWSIZE_Y)
			line_height = WINDOWSIZE_Y;

		
		line(game, vec2i(WINDOWSIZE_X / 2 + i * 1000, WINDOWSIZE_Y - line_height * 50), vec2i(WINDOWSIZE_X / 2 + i * 1000, WINDOWSIZE_Y + line_height * 50), rgbtocolor(255,0,0));




		i += 0.01;
	}
	
	
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
