# include "../includes/cub3D.h"


void press_forward(t_game *game)
{
    if ((game->charmap[(int)floor(game->player.inv_pos.x + game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] != '1'  && \
        game->charmap[(int)floor(game->player.inv_pos.x + game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] != 'D')  || \
        (game->charmap[(int)floor(game->player.inv_pos.x + game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] == 'D' && \
        this_door_open(game, (int)floor(game->player.inv_pos.x + game->player.dirX * MOVESPEED), (int)floor(game->player.inv_pos.y))))
            game->player.inv_pos.x += game->player.dirX * MOVESPEED;
    if ((game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y + game->player.dirY * MOVESPEED)] != '1'  && \
        game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y + game->player.dirY * MOVESPEED)] != 'D')  || \
        (game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y + game->player.dirY * MOVESPEED)] == 'D' && \
        this_door_open(game, (int)floor(game->player.inv_pos.x), (int)floor(game->player.inv_pos.y + game->player.dirY * MOVESPEED))))
            game->player.inv_pos.y += game->player.dirY * MOVESPEED;
}

void press_left(t_game *game)
{
    double oldDirX = game->player.dirX;
    game->player.dirX = game->player.dirX * cos(ROTATESPEED) - game->player.dirY * sin(ROTATESPEED);
    game->player.dirY = oldDirX * sin(ROTATESPEED) + game->player.dirY * cos(ROTATESPEED);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(ROTATESPEED) - game->player.planeY * sin(ROTATESPEED);
    game->player.planeY = oldPlaneX * sin(ROTATESPEED) + game->player.planeY * cos(ROTATESPEED);
}

void press_back(t_game *game)
{
    if ((game->charmap[(int)floor(game->player.inv_pos.x - game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] != '1' && \
        game->charmap[(int)floor(game->player.inv_pos.x - game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] != 'D') || \
        (game->charmap[(int)floor(game->player.inv_pos.x - game->player.dirX * MOVESPEED)][(int)floor(game->player.inv_pos.y)] == 'D' && \
        this_door_open(game, (int)floor(game->player.inv_pos.x - game->player.dirX * MOVESPEED), (int)floor(game->player.inv_pos.y))))
        game->player.inv_pos.x -= game->player.dirX * MOVESPEED;
    if ((game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y - game->player.dirY * MOVESPEED)] != '1' && \
        game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y - game->player.dirY * MOVESPEED)] != 'D') || \
        (game->charmap[(int)floor(game->player.inv_pos.x)][(int)floor(game->player.inv_pos.y - game->player.dirY * MOVESPEED)] == 'D' && \
        this_door_open(game, (int)floor(game->player.inv_pos.x), (int)floor(game->player.inv_pos.y - game->player.dirY * MOVESPEED))))
        game->player.inv_pos.y -= game->player.dirY * MOVESPEED;
}

void press_right(t_game *game)
{
    double oldDirX = game->player.dirX;
    game->player.dirX = game->player.dirX * cos(-ROTATESPEED) - game->player.dirY * sin(-ROTATESPEED);
    game->player.dirY = oldDirX * sin(-ROTATESPEED) + game->player.dirY * cos(-ROTATESPEED);
    double oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * cos(-ROTATESPEED) - game->player.planeY * sin(-ROTATESPEED);
    game->player.planeY = oldPlaneX * sin(-ROTATESPEED) + game->player.planeY * cos(-ROTATESPEED);
}

int key_event(int key, t_game *game)
{
    if      (key == ESC)
        close_game(game);
	else if (key == W)
        press_forward(game);
	else if (key == A)
        press_left(game);
	else if (key == S)
        press_back(game);
	else if (key == D)
        press_right(game);   
	else if (key == SPACE)
		door_action(game, ppos.x, ppos.y);
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

//int p_move(t_game *game, int ns, int ew)
//{
//    t_vec2f newpos;
//
//    if (ns + ew < -2 || ns + ew > 2)
//        return (0);
//    newpos.x = ppos.x + cos(prt) * ns * WALKDIST;
//    newpos.y = ppos.y + sin(prt) * ew * WALKDIST;
//
//	if (coordcheck(game, newpos.x / SQUARESIZE, newpos.y / SQUARESIZE) == '1' || \
		(coordcheck(game, newpos.x / SQUARESIZE, newpos.y / SQUARESIZE) == 'D' && \
		this_door_open(game, newpos.x, newpos.y) == 0))
//	{
//		// ppos.x = (int)ppos.x;
//		// ppos.y = (int)ppos.y;
//	}
//	else
//    	ppos = newpos;
//}
