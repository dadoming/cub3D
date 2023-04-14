# include "../includes/cub3D.h"

static void	intbin_append(int *color, unsigned char fam)
{
	*color = *color << 8;
	*color = *color | fam;
}

int	rgbtocolor(unsigned char r, unsigned char g, unsigned char b)
{
	int		color;

	color = 127;
	intbin_append(&color, r);
	intbin_append(&color, g);
	intbin_append(&color, b);
	return (color);
}