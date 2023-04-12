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

int	verline(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		mlx_pixel_put(game->mlx, game->win, pos.x, pos.y + i, color);
		i++;
	}
	return (1);
}

int	pixsquare(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pos.y += 1;
		horline(game, pos, size, color);
		i++;
	}
	return (1);

}
