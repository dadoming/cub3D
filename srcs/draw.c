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
	
	vec.y = 0;
	while (game->charmap[vec.y] != NULL)
	{
		vec.x = 0;
		while (game->charmap[vec.y][vec.x] != '\0')
		{
			if (game->charmap[vec.y][vec.x] == WALL)
				square_prop(game, vec, 1, rgbtocolor(255, 255, 255));
			else if (game->charmap[vec.y][vec.x] == DOOR)
				square_prop(game, vec, 1, rgbtocolor(255, 255, 0));
			else if (ft_charinside(game->charmap[vec.y][vec.x], "NSWE"))
				square_prop(game, vec, 1, rgbtocolor(255, 0, 0));
			vec.x += 1;
		}
		vec.y += 1;
	}
	return (1);
}

int	draw_player(t_game *game)
{
	pixsquare(game, vec2i(px, py), 10, rgbtocolor(128,20,100));
	line_tf(game, game->player.pos, 80, rgbtocolor(128,0,20));

	return (1);
}

void draw_checkerboard(t_game *game, t_vec2i start, size_t q, size_t pixelsize)
{
	size_t	x;
	size_t	y;

	x = 0;
	while (x <= q)
	{
		verline(game, vec2i(start.x + pixelsize*x, start.y), q*pixelsize, 0);
		x += 1;
	}
	y = 0;
	while (y <= q)
	{
		horline(game, vec2i(start.x, start.y + pixelsize*y), q*pixelsize, 0);
		y += 1;
	}

}