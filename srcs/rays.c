# include "../includes/cub3D.h"

void drawVertical(t_game *game, int x, t_vec2i y, t_object *ob);

void	draw_ray(t_game *game)
{
    int x = 0;
    while (x < WINDOWSIZE_X)
    {
        double cameraX = 2 * x / (double)WINDOWSIZE_X - 1;
        double rayDirX = game->player.dirX  + game->player.planeX * cameraX;
        double rayDirY = game->player.dirY + game->player.planeY * cameraX;

        int mapX = (int)game->player.inv_pos.x;
        int mapY = (int)game->player.inv_pos.y;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (game->player.inv_pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player.inv_pos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (game->player.inv_pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player.inv_pos.y) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->objmap[mapX][mapY] && (game->objmap[mapX][mapY]->type == WALL || game->objmap[mapX][mapY]->type == DOOR))
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        
        int lineHeight = (int)(WINDOWSIZE_Y / perpWallDist);

        int drawStart = -lineHeight / 2 + WINDOWSIZE_Y / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + WINDOWSIZE_Y / 2;
        if (drawEnd >= WINDOWSIZE_Y)
            drawEnd = WINDOWSIZE_Y - 1;

        //line (game, vec2i(game->player.inv_pos.y * SQUARESIZE, game->player.inv_pos.x* SQUARESIZE), vec2i(mapX* SQUARESIZE, mapY* SQUARESIZE), rgbtocolor(255, 0, 0));
        drawVertical(game, x, vec2i(drawStart, drawEnd), game->objmap[mapX][mapY]);
        x++;
    }
}

void drawVertical(t_game *game, int x, t_vec2i y, t_object *ob)
{
    int i = y.x;
    int color;

    if (ob == NULL)
        return ;
    if (x == (WINDOWSIZE_X / 2))
        game->select = ob;
    while (i < y.y)
    {
        mypixelput(&game->imgbuffer, x, i, ob->get_image(ob, 0));
        i++;
    }
}
