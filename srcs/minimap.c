# include "../includes/cub3D.h"

/*
    In case the player is in the corner of the map, 
        he will always be at minimum in square 2, 2.
    So he's always at x,y at least:
      - charmap limit (0+2, 0+2) in case of (0, 0).
      - charmap limit (max-2, max-2) in case of (max, max).
      - charmap limit (0+2, max-2) in case of (0, max).
      - charmap limit (max-2, 0+2) in case of (max, 0).

    So we can always add the first two cubes to the minimap image to a square
        and set the size of the minimap image to 32 * 5 = 160 pixels.
    
*/

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

void draw_full_minimap(t_game *game)
{
    draw_minimap_map(game);
}

static void	my_minimap_pixelput(t_imgbuffer *imgbuffer, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || y < 0)
		return ;
	if (x > MINIMAPSIZE_X || y > MINIMAPSIZE_Y)
		return ;
	pixel = imgbuffer->addr + imgbufferoffset(imgbuffer, x, y);
	*(unsigned int*)pixel = color;
}

void add_square(t_imgbuffer *imgbuffer, t_vec2i vec, int size_square, int color)
{
    int i;
    int j;

    i = 0;
    while (i < size_square)
    {
        j = 0;
        while (j < size_square)
        {
            my_minimap_pixelput(imgbuffer, vec.x + i, vec.y + j, color);
            j++;
        }
        i++;
    }
}

void load_minimap_image(t_game *game, t_vec2i player_pos)
{
	int color;
    t_vec2i vec;
    t_vec2i minimap_vec;

    vec.y = player_pos.y - 2;
    minimap_vec.y = MINIMAPBORDER;
    minimap_vec.x = MINIMAPBORDER;
    while (minimap_vec.y < MINIMAPSIZE_Y)
    {
        vec.x = player_pos.x - 2;
        minimap_vec.x = MINIMAPBORDER;
        while (minimap_vec.x < MINIMAPSIZE_X)
        {
            if (game->charmap[vec.y][vec.x] == WALL)
                color = 0x00D27D2D;
            else if(game->charmap[vec.y][vec.x] == DOOR)
                color = 0x00FFD700;
            else
                color = 0x00FFFFFF;
            add_square(&game->imgbuffer, minimap_vec, 32, color);
            minimap_vec.x += 32;
            vec.x++;
        }
        minimap_vec.y += 32;
        vec.y++;
    }
}

void load_minimap_border(t_game *game)
{
    t_vec2i minimap_coords;
 
    minimap_coords.y = 0;
    while (minimap_coords.y < MINIMAPSIZE_Y + MINIMAPBORDER)
    {
        minimap_coords.x = 0;
        while (minimap_coords.x < MINIMAPSIZE_X + MINIMAPBORDER)
        {
            if (minimap_coords.y < MINIMAPBORDER || minimap_coords.x < MINIMAPBORDER || \
                minimap_coords.y >= MINIMAPSIZE_Y || minimap_coords.x >= MINIMAPSIZE_X)
            {
                add_square(&game->imgbuffer, minimap_coords, MINIMAPBORDER, 0x00800020);
            }
            minimap_coords.x += MINIMAPBORDER;
        }
        minimap_coords.y += MINIMAPBORDER;
    }
}

void load_player(t_game *game)
{
    t_vec2i vec;
    int color;

    vec.y = MINIMAPSIZE_Y / 5 * 3 - 16 + 8 - 4 + 1;
    vec.x = MINIMAPSIZE_X / 5 * 3 - 16 + 4;
    color = 0x00FF0000;
    add_square(&game->imgbuffer, vec, 8, color);
}

void draw_minimap(t_game *game, t_vec2f player_pos)
{
    t_vec2i vec;
    
    vec.y = (int)(player_pos.x);
    vec.x = (int)(player_pos.y);
    load_minimap_border(game);
    load_minimap_image(game, vec);
    load_player(game);
    //mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
}

