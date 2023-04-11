# include "../includes/cub3D.h"

int	horline(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		mlx_pixel_put(game->mlx, game->win, pos.x + i, pos.y, color);
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

int	line(t_game *game, t_vec2i origin, t_vec2i dest, int color)
{
	lineNaive(game, origin, dest, color);
	// lineBresenham(game, origin, dest, color);
}
