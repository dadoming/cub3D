# include "../includes/cub3D.h"

int collision(t_game *game, int x, int y)
{
    t_object *obj;

    obj = game->objmap[x][y];
    if (obj == NULL)
        return (1);
    if (obj->type == DOOR && ((t_door *) obj)->state)
        return (1);
    return (0);
}

void rotate_direction(t_game *game, double angle_x, double angle_y)
{
    double oldDirX;
    double oldPlaneX;

    oldDirX = game->player.dirX;
    game->player.dirX = game->player.dirX * angle_x - game->player.dirY * angle_y;
    game->player.dirY = oldDirX * angle_y + game->player.dirY * angle_x;
    oldPlaneX = game->player.planeX;
    game->player.planeX = game->player.planeX * angle_x - game->player.planeY * angle_y;
    game->player.planeY = oldPlaneX * angle_y + game->player.planeY * angle_x;
}

void press_forward(t_game *game)
{
    if (collision(game, floor(game->player.inv_pos.x + game->player.dirX * MOVESPEED), floor(game->player.inv_pos.y)))
            game->player.inv_pos.x += game->player.dirX * MOVESPEED;
    if (collision(game, floor(game->player.inv_pos.x), floor(game->player.inv_pos.y + game->player.dirY * MOVESPEED)))
            game->player.inv_pos.y += game->player.dirY * MOVESPEED;
}

void press_back(t_game *game)
{
    if (collision(game, floor(game->player.inv_pos.x - game->player.dirX * MOVESPEED), floor(game->player.inv_pos.y)))
        game->player.inv_pos.x -= game->player.dirX * MOVESPEED;
    if (collision(game, floor(game->player.inv_pos.x), floor(game->player.inv_pos.y - game->player.dirY * MOVESPEED)))
        game->player.inv_pos.y -= game->player.dirY * MOVESPEED;
}

void press_left(t_game *game)
{
    if (collision(game, floor(game->player.inv_pos.x - game->player.planeX * MOVESPEED), floor(game->player.inv_pos.y)))
        game->player.inv_pos.x -= game->player.planeX * MOVESPEED;
    if (collision(game, floor(game->player.inv_pos.x), floor(game->player.inv_pos.y - game->player.planeY * MOVESPEED)))
        game->player.inv_pos.y -= game->player.planeY * MOVESPEED;
}

void press_right(t_game *game)
{
    if (collision(game, floor(game->player.inv_pos.x + game->player.planeX * MOVESPEED), floor(game->player.inv_pos.y)))
        game->player.inv_pos.x += game->player.planeX * MOVESPEED;
    if (collision(game, floor(game->player.inv_pos.x), floor(game->player.inv_pos.y + game->player.planeY * MOVESPEED)))
        game->player.inv_pos.y += game->player.planeY * MOVESPEED;
}

int key_event(int key, t_game *game)
{
    if      (key == ESC)
        close_game(game);
	else if (key == W)
        press_forward(game);
	else if (key == A)
    {
        press_left(game); // make this permanent and comment rotate_direction for evaluation(?)
        //rotate_direction(game, cos(ROTATESPEED), sin(ROTATESPEED));
    }
	else if (key == S)
        press_back(game);
	else if (key == D)
    {
        press_right(game); // make this permanent and comment rotate_direction for evaluation(?)
        //rotate_direction(game, cos(-ROTATESPEED), sin(-ROTATESPEED));
    }
	else if (key == SPACE && game->select && game->select->action)
		game->select->action(game->select, game);
	else if (key == CTRL)
	{
        game->minimap_toggle = !game->minimap_toggle;
	}
    else if (key == SHIFT)
    {
        game->player_shoot.trigger = 1;
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
