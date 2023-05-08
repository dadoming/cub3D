# include "../../includes/menu.h"

void	clear_img(t_menu *menu)
{
	size_t	j;
	size_t	i;

	j = 0;
	while (j < WINDOWSIZE_Y)
	{
		i = 0;
		while (i < WINDOWSIZE_X)
		{
			my_pput(&menu->imgbuffer, i, j, 0x00000000);
			i++;
		}
		j++;
	}
}

int	imgbuf_offset(t_img *imgbuffer, int x, int y)
{
	return (y * imgbuffer->line_length + x * (imgbuffer->bits_per_pixel / 8));
}

void	my_pput(t_img *imgbuffer, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0)
		return ;
	if (x > WINDOWSIZE_X || y > WINDOWSIZE_Y)
		return ;
    pixel = imgbuffer->addr + imgbuf_offset(imgbuffer, x, y);
    *(unsigned int*)pixel = color;
}
