# include "../includes/cub3D.h"

#define ppos game->player.pos

char	coordcheck(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return 0;
	else if (x >= WINDOWSIZE_X || y >= WINDOWSIZE_Y)
		return 0;
	else if (y >= ft_mtrxlen(game->charmap))
		return 0;
	else if (x >= ft_strlen(game->charmap[0]))
		return 0;
	else
		return (game->charmap[y][x]);
}

int p_move(t_game *game, int ns, int ew)
{
    t_vec2f newpos;

    if (ns + ew < -2 || ns + ew > 2)
        return (0);
    newpos.x = ppos.x + cos(game->player.theta) * ns;;
    newpos.y = ppos.y + sin(game->player.theta) * ew;;

	//TODO: check collisions!
	//Do not need to check because there will always be
	// '1' wall padding
	if (game->charmap[(int)newpos.y][(int)newpos.x] == '1')
		(void)NULL;
	else
    	ppos = newpos;
	// _

    printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
    printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);    
}
