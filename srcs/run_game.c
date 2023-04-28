# include "../includes/cub3D.h"

void draw_minimap_border(t_game *game)
{
    t_vec2i pos;

    pos.y = 0;
    while (pos.y < (game->mapsize.y - 1) * MINIMAPSCALE + MINIMAPBORDER)
    {
        pos.x = 0;
        while (pos.x < (game->mapsize.x-1) * MINIMAPSCALE + MINIMAPBORDER)
        {
            if (pos.y < (game->mapsize.y - 1) * MINIMAPSCALE + MINIMAPBORDER || pos.x < (game->mapsize.x-1) * MINIMAPSCALE + MINIMAPBORDER || \
                pos.y >= game->mapsize.y || pos.x >= game->mapsize.x)
            {
                add_square(&game->imgbuffer, pos, MINIMAPBORDER, 0x00800020);
            }
            pos.x += MINIMAPBORDER;
        }
        pos.y += MINIMAPBORDER;
    }
}

void	square_prop_minimap(t_game *game, t_vec2i pos, size_t size, int color)
{
	size_t	i;

	pos.x = pos.x * MINIMAPSCALE;
	pos.y = pos.y * MINIMAPSCALE;

	size = size * MINIMAPSCALE;

	i = 0;
	while (i < size)
	{
		horline(game, pos, size, color);
		pos.y += 1;
		i++;
	}
}

int	draw_minimap_map(t_game *game)
{
	t_vec2i	vec;
	
	vec.y = 0;
	while (game->charmap[vec.y] != NULL)
	{
		vec.x = 0;
		while (game->charmap[vec.y][vec.x] != '\0')
		{
			if (game->charmap[vec.y][vec.x] == WALL)
				square_prop_minimap(game, vec, 1, 0x00D27D2D);
			else if (game->charmap[vec.y][vec.x] == DOOR)
				square_prop_minimap(game, vec, 1, 0x00FFD700);
			vec.x += 1;
		}
		vec.y += 1;
	}
	return (1);
}

int	draw_minimap_player(t_game *game)
{
	pixsquare(game, vec2i(px, py), 2, rgbtocolor(0,20,100));
	//line_tf(game, game->player.pos, 80, rgbtocolor(128,0,20));

	return (1);
}

void draw_full_minimap(t_game *game)
{
    draw_minimap_border(game);
    draw_minimap_map(game);
    draw_minimap_player(game);
}

int	theloop(t_game *game)
{
	myclearimg(game);
	draw_map(game);
	draw_player(game);
	draw_ray(game);
	if (game->minimap_toggle == 0)
	{
		draw_minimap(game, game->player.pos); // in int
    	//draw_full_minimap(game);
	}
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}