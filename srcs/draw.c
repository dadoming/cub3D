# include "../includes/cub3D.h"

#define SQUARESIZE 5
int	draw_map(t_game *game)
{
	size_t	j;
	size_t	i;
	t_vec2i	vec;
	
	j = 0;
	vec.y = 50;
	while (game->charmap[j] != NULL)
	{
		i = 0;
		vec.x = 50;
		while (game->charmap[j][i] != '\0')
		{
			if (game->charmap[j][i] == WALL)
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(23, 128, 250));
			else if (game->charmap[j][i] == FLOOR)
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(23, 128, 20));
			else if (ft_charinside(game->charmap[j][i], "NSWE"))
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(255, 0, 0));
			
			vec.x += SQUARESIZE;
			i++;
		}
		vec.y += SQUARESIZE;
		j++;
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
		mlx_pixel_put(game->mlx, game->win, x, y, color);
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
		mlx_pixel_put(game->mlx, game->win, x, y, color);
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
}