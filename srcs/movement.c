# include "../includes/cub3D.h"

#define ppos game->player.pos

#define WALKDIST 1


int p_move(t_game *game, int ns, int ew)
{
    t_vec2f newpos;

    if (ns + ew < -2 || ns + ew > 2)
        return (0);
    newpos.x = ppos.x + cos(game->player.theta) * ns;
    newpos.y = ppos.y + sin(game->player.theta) * ew;

    ppos = newpos;
    // if (fabs(ppos.x) > WALKDIST)
    // {
    //     game->player.pos.x += 1; //TODO: protect!
    //     ppos.x = 0;
    // }
    // // else if (fabs(ppos.x) < 0)
    // if (fabs(ppos.y) < 0)
    // {
    //     game->player.pos.y += 1; //TODO: protect!
    //     ppos.y = 0;
    // }
    printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
    printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);
    
}

// int p_movefrwd(t_game *game)
// {
//     t_vec2f newpos;

//     newpos.x = ppos.x + cos(game->player.theta);
//     newpos.y = ppos.y + sin(game->player.theta);

//     ppos = newpos;
//     // if (fabs(ppos.x) > WALKDIST)
//     // {
//     //     game->player.pos.x += 1; //TODO: protect!
//     //     ppos.x = 0;
//     // }
//     // // else if (fabs(ppos.x) < 0)
//     // if (fabs(ppos.y) < 0)
//     // {
//     //     game->player.pos.y += 1; //TODO: protect!
//     //     ppos.y = 0;
//     // }
//     printf("(%d,%d)__", (int)game->player.pos.x, (int)game->player.pos.y);
//     printf("(%f,%f)\n", game->player.pos.x, game->player.pos.y);
// }



// int p_movebkwd(t_game *game)
// {
//     ppos.x -= cos(game->player.theta);
//     ppos.y += sin(game->player.theta);
//     if (fabs(ppos.x) > WALKDIST)
//     {
//         game->player.pos.x--; //TODO: protect!
//         game->player.pposset.x = 0;
//     }
//     if (fabs(ppos.y) > WALKDIST)
//     {
//         game->player.pos.y--; //TODO: protect!
//         game->player.pposset.y = 0;
//     }
//     printf("(%d,%d)__", game->player.pos.x, game->player.pos.y);
//     printf("(%f,%f)\n", game->player.pposset.x, game->player.pposset.y);
// }
