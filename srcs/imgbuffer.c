# include "../includes/cub3D.h"

int	imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y)
{
	return (y * imgbuffer->line_length + x * (imgbuffer->bits_per_pixel / 8));
}

int mypixelget(t_imgbuffer *imgbuffer, int x, int y)
{
    int color;
    int offset;

    offset = imgbufferoffset(imgbuffer, x, y);
    color = *(int *)(imgbuffer->addr + offset);
    return (color);
}
