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

int	pixsquaref(t_game *game, t_vec2f pos, size_t size, int color)
{
	t_vec2i	tmp;
	size_t	i;

	tmp.x = pos.x;
	tmp.y = pos.y;
	i = 0;
	while (i < size)
	{
		pos.y += 1;
		horline(game, tmp, size, color);
		i++;
	}
	return (1);

}

int	pixsquarecent(t_game *game, t_vec2f pos, size_t size, int color)
{
	t_vec2i	tmp;
	size_t	i;

	tmp.x = pos.x - size/2;
	tmp.y = pos.y - size/2;
	i = 0;
	while (i < size)
	{
		tmp.y += 1;
		horline(game, tmp, size, color);
		i++;
	}
	return (1);

}