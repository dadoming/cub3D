# include "../includes/cub3D.h"

int key_event(int key, t_game *game)
{
    //printf("key> %d\n", key);
    if (key == ESC)
	{
		printf("ESC\n");
        close_game(game);
		// printf("%i\n", (int)(1.5f - 0.3f));
	}
	else if (key == A)
	{
		game->player.theta += M_PI / RADJUMP;
		if (pt> 2 * M_PI)
			pt-= 2 * M_PI;
		printf("%f\n", game->player.theta);
	}
	else if (key == D)
	{
		game->player.theta -= M_PI / RADJUMP;
		if (pt< 0)
			pt+= 2 * M_PI;
		printf("%f\n", game->player.theta);
	}
	else if (key == W)
	{
		p_move(game, 1, 1);
	}
	else if (key == S)
	{
		p_move(game, -1, -1);
	}
    return (0);
}

char	coordcheck(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return 0;
	else if (x >= WINDOWSIZE_X || y >= WINDOWSIZE_Y)
		return 0;
	else if (y >= (long long)ft_mtrxlen((void **)game->charmap))
		return 0;
	else if (x >= (long)ft_strlen(game->charmap[0]))
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

	if (coordcheck(game, newpos.x / SQUARESIZE, newpos.y / SQUARESIZE) == '1')
	{
		// ppos.x = (int)ppos.x;
		// ppos.y = (int)ppos.y;
	}
	else
    	ppos = newpos;

    printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
    printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);    
}
