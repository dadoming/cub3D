# include "../includes/cub3D.h"

void	myclearimg(t_game *game)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < WINDOWSIZE_Y)
	{
		i = 0;
		while (i < WINDOWSIZE_X)
		{
			mypixelput(&game->imgbuffer, i, j, rgbtocolor(0,0,0));
			i++;
		}
		j++;
	}
}

void	mypixelput(t_imgbuffer *imgbuffer, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0)
		return ;
	if (x > WINDOWSIZE_X || y > WINDOWSIZE_Y)
		return ;
	pixel = imgbuffer->addr + imgbufferoffset(imgbuffer, x, y);
	*(unsigned int*)pixel = color;
}

int	draw_map(t_game *game)
{
	t_vec2i	vec;
	
	vec.y = 00;
	while (game->charmap[vec.y] != NULL)
	{
		vec.x = 00;
		while (game->charmap[vec.y][vec.x] != '\0')
		{
			if (game->charmap[vec.y][vec.x] == WALL)
				square_prop(game, vec, 1, rgbtocolor(23, 128, 250));
			else if (game->charmap[vec.y][vec.x] == FLOOR)
				square_prop(game, vec, 1, rgbtocolor(23, 128, 20));
			else if (ft_charinside(game->charmap[vec.y][vec.x], "NSWE"))
				square_prop(game, vec, 1, rgbtocolor(255, 0, 0));
			else
				square_prop(game, vec, 1, rgbtocolor(128,128,128));
			vec.x += 1;
		}
		vec.y += 1;
	}
	return (1);
}

int	draw_player(t_game *game)
{
	square_propf(game, game->player.pos, 1, rgbtocolor(128, 20, 100));
	line_prop(game, game->player.pos, 10, rgbtocolor(255, 50, 50));

	return (1);
}