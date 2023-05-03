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
