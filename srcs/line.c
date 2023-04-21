# include "../includes/cub3D.h"

int	horline(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		mypixelput(&game->imgbuffer, pos.x + i, pos.y, color);
		i++;
	}
	return (1);
}

int	verline(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		mypixelput(&game->imgbuffer, pos.x, pos.y + i, color);
		i++;
	}
	return (1);
}


int	lineNaive(t_game *game, t_vec2i origin, t_vec2i dest, int color)
{
	int	dx;
	int dy;
	int	x;
	int	y;

	// if (dest.x < origin.x)
	// 	return (line(game, dest, origin, color));

	dx = dest.x - origin.x;
	dy = dest.y - origin.y;

	x = origin.x;
	while (x < dest.x)
	{
		y = origin.y + dy * (x - origin.x) / dx;
		// y = origin.y + dy / dx;
		mypixelput(&game->imgbuffer, x, y, color);
		x++;
	}
}

/**
 * Not working
*/
int	lineBresenham(t_game *game, t_vec2i origin, t_vec2i dest, int color)
{
	int	dx;
	int dy;
	int	d;
	int	x;
	int	y;

	// if (dest.x < origin.x)
	// 	return (line(game, dest, origin, color));

	dx = dest.x - origin.x;
	dy = dest.y - origin.y;

	d = (2 * dy) - dx;

	y = origin.y;
	x = origin.x;
	while (x < dest.x)
	{
		mypixelput(&game->imgbuffer, x, y, color);
		if (d > 0)
		{
			y += 1;
			d = d - (2 * dx);
		}
		d = d + (2 * dy);
		x++;
	}
}

#define APPROX 1
int	line(t_game *game, t_vec2i origin, t_vec2i dest, int color)
{
	int	adx;
	int	ady;

	adx = abs(dest.x - origin.x);
	ady = abs(dest.y - origin.y);

	if (adx <= APPROX)
	{
		if (origin.y <= dest.y)
			origin.y += 0;
		else
			origin.y += -ady;
		verline(game, origin, ady, color);
	}
	else if (ady <= APPROX)
	{
		if (origin.x <= dest.x)
			origin.x += -0;
		else
			origin.x += -adx;
		horline(game, origin, adx, color);
	}
	else if (origin.x <= dest.x)
		lineNaive(game, origin, dest, color);
	else
		lineNaive(game, dest, origin, color);
}

// int	line_s(t_game *game, t_vec2i origin, size_t size, int color)
// {
// 	t_vec2i	dest;

// 	dest.x = origin.x + game->player.direction.x * size;
// 	dest.y = origin.y + game->player.direction.y * size;
// 	line(game, origin, dest, color);
// 	// lineBresenham(game, origin, dest, color);
// }

int	line_t(t_game *game, t_vec2i origin, size_t size, int color)
{
	t_vec2i	dest;

	dest.x = origin.x + cos(game->player.theta) * size;
	dest.y = origin.y + sin(game->player.theta) * size;
	line(game, origin, dest, color);
}

int	line_tf(t_game *game, t_vec2f origin, size_t size, int color)
{
	t_vec2i	tmp;
	t_vec2i	dest;

	tmp.x = origin.x;
	tmp.y = origin.y;

	dest.x = tmp.x + cos(game->player.theta) * size;
	dest.y = tmp.y + sin(game->player.theta) * size;
	line(game, tmp, dest, color);
	return (1);
}

int	line_prop(t_game *game, t_vec2f origin, size_t size, int color)
{
	origin.x = origin.x * SQUARESIZE;
	origin.y = origin.y * SQUARESIZE;
	line_tf(game, origin, size * SQUARESIZE, color);
}

int	line_odprop(t_game *game, t_vec2f origin, t_vec2f dest, int color)
{
	int	adx;
	int	ady;

	origin.x *= SQUARESIZE;
	origin.y *= SQUARESIZE;
	dest.x *= SQUARESIZE;
	dest.y *= SQUARESIZE;

	adx = fabs(dest.x - origin.x);
	ady = fabs(dest.y - origin.y);

	if (adx <= APPROX)
	{
		if (origin.y <= dest.y)
			origin.y += 0;
		else
			origin.y += -ady;
		verline(game, vec2i(origin.x, origin.y), ady, color);
	}
	else if (ady <= APPROX)
	{
		if (origin.x <= dest.x)
			origin.x += -0;
		else
			origin.x += -adx;
		horline(game, vec2i(origin.x, origin.y), adx, color);
	}
	else if (origin.x <= dest.x)
		lineNaive(game, vec2i(origin.x, origin.y), vec2i(dest.x, dest.y), color);
	else
		lineNaive(game, vec2i(dest.x, dest.y), vec2i(origin.x, origin.y), color);
}
