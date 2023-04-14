# include "../includes/cub3D.h"

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