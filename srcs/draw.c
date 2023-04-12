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
			if (game->charmap[j][i] == '1')
				pixsquare(game, vec, SQUARESIZE, rgbtocolor(23, 128, 250));
			else if (game->charmap[j][i] == '0')
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
