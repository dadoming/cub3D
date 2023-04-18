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
	pixel = imgbuffer->addr + imgbufferoffset(imgbuffer, x, y);
	// pixel = 
	*(unsigned int*)pixel = color;
}

int	draw_map(t_game *game)
{
	size_t	j;
	size_t	i;
	t_vec2i	vec;
	
	j = 0;
	vec.y = 00;
	while (game->charmap[j] != NULL)
	{
		i = 0;
		vec.x = 00;
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

int	draw_player(t_game *game)
{
	t_vec2f	drawpos;

	drawpos.x = game->player.pos.x * SQUARESIZE;
	drawpos.y = game->player.pos.y * SQUARESIZE;

	pixsquarecent(game, drawpos, SQUARESIZE, rgbtocolor(0, 255, 0));
	line_tf(game, drawpos, 150, rgbtocolor(255, 50, 50));

	return (1);
}