# include "../includes/cub3D.h"

#define ppos game->player.pos

#define WALKDIST 1


int p_move(t_game *game, int ns, int ew)
{
    t_vec2f newpos;

    if (ns + ew < -2 || ns + ew > 2)
        return (0);
    newpos.x = ppos.x + cos(game->player.theta) * ns * WALKDIST;
    newpos.y = ppos.y + sin(game->player.theta) * ew * WALKDIST;

	//TODO: check collisions!

    ppos = newpos;

    printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
    printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);    
}
