# include "../includes/cub3D.h"

void door_action(t_game *game, int x, int y)
{
	int i = 0;
	while (i < game->door_count)
	{
		if (abs(game->door[i].x - x / SQUARESIZE) == 1 && abs(game->door[i].y - y / SQUARESIZE) == 0)
		{
			if (game->door[i].state == 0)
				game->door[i].state = 1;
			else
				game->door[i].state = 0;
		}
		else if (abs(game->door[i].x - x) == 0 && abs(game->door[i].y - y) == 1)
		{
			if (game->door[i].state == 0)
				game->door[i].state = 1;
			else
				game->door[i].state = 0;
		}
		i++;
	}
}

int key_event(int key, t_game *game)
{
    if (key == ESC)
	{
		printf("ESC\n");
        close_game(game);
	}
	else if (key == A)
	{
		game->player.theta += M_PI / RADJUMP;
		if (pt> 2 * M_PI)
			pt-= 2 * M_PI;
	}
	else if (key == D)
	{
		game->player.theta -= M_PI / RADJUMP;
		if (pt< 0)
			pt+= 2 * M_PI;
	}
	else if (key == W)
	{
		p_move(game, 1, 1);
	}
	else if (key == S)
	{
		p_move(game, -1, -1);
	}
	else if (key == SPACE)
	{
		door_action(game, ppos.x, ppos.y);
	}
	else if (key == CTRL)
	{
		if (game->minimap_toggle == 1)
			game->minimap_toggle = 0;
		else
			game->minimap_toggle = 1;
	}
    return (0);
}

char	coordcheck(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return 0;
	else if (x >= WINDOWSIZE_X || y >= WINDOWSIZE_Y)
		return 0;
	else if (y >= game->mapsize.y)
		return 0;
	else if (x >= game->mapsize.x)
		return 0;
	else
		return (game->charmap[y][x]);
}

char	coordcheck_prop(t_game *game, int x, int y)
{
	return (coordcheck(game, x / SQUARESIZE, y / SQUARESIZE));
}

int p_move(t_game *game, int ns, int ew)
{
    t_vec2f newpos;

    if (ns + ew < -2 || ns + ew > 2)
        return (0);
    newpos.x = ppos.x + cos(prt) * ns * WALKDIST;
    newpos.y = ppos.y + sin(prt) * ew * WALKDIST;

	if (coordcheck(game, newpos.x / SQUARESIZE, newpos.y / SQUARESIZE) == '1' || \
		(coordcheck(game, newpos.x / SQUARESIZE, newpos.y / SQUARESIZE) == 'D' && \
		this_door_open(game, newpos.x, newpos.y) == 0))
	{
		// ppos.x = (int)ppos.x;
		// ppos.y = (int)ppos.y;
	}
	else
    	ppos = newpos;
}
