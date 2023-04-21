# include "../includes/cub3D.h"

#define ppos game->player.pos

char	coordcheck(t_game *game, int x, int y)
{
	// x += 1;
	// y += 1;
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

int p_move(t_game *game, int ns, int ew)
{
    t_vec2f newpos;

    if (ns + ew < -2 || ns + ew > 2)
        return (0);
    newpos.x = ppos.x + cos(game->player.theta) * ns;// * WALKDIST;
    newpos.y = ppos.y + sin(game->player.theta) * ew;// * WALKDIST;

	// if (coordcheck(game, newpos.x, newpos.y) == '1')
	// {
	// 	// ppos.x = (int)ppos.x;
	// 	// ppos.y = (int)ppos.y;
	// }
	// else
    	ppos = newpos;

    printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
    printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);    
}
