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

void	square_prop(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	pos.x = (1 + pos.x) * SQUARESIZE;
	pos.y = (1 + pos.y) * SQUARESIZE;

	i = 0;
	while (i < size * SQUARESIZE)
	{
		pos.y += 1;
		horline(game, pos, size, color);
		i++;
	}
}


/**
 * Not centered Square that is "printed" with proportions.
 * That means it's real value is different from it's representation
*/
void	square_propf(t_game *game, t_vec2f pos, size_t size, int color)
{
	t_vec2i	tmp;
	tmp.x = pos.x * SQUARESIZE;
	tmp.y = pos.y * SQUARESIZE;
	square_prop(game, tmp, size, color);

}

/**
 * Centered Square that is "printed" with proportions.
 * That means it's real value is different from it's representation
*/
void	squarecent_prop(t_game *game, t_vec2f pos, size_t size, int color)
{
	t_vec2i	tmp;
	size_t	i;

	tmp.x = pos.x * SQUARESIZE - size/2;
	tmp.y = pos.y * SQUARESIZE  - size/2;

	i = 0;
	while (i < size)
	{
		tmp.y += 1;
		horline(game, tmp, size, color);
		i++;
	}
}
