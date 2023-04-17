# include "../includes/cub3D.h"

int	imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y)
{
	return (y * imgbuffer->line_length + x * (imgbuffer->bits_per_pixel / 8));
}

// void	imgbufferset(t_imgbuffer *imgbuffer)
// {

// }
