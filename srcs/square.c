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
