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

        // new

        double wallX;
        if (side == 0)
            wallX = game->player.inv_pos.y + perpWallDist * rayDirY;
        else
            wallX = game->player.inv_pos.x + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)SQUARESIZE);
        if (side == 0 && rayDirX > 0)
            texX = SQUARESIZE - texX - 1;
        if (side == 1 && rayDirY < 0)
            texX = SQUARESIZE - texX - 1;


        double step = 1.0 * SQUARESIZE / lineHeight;
        double texPos = (drawStart - WINDOWSIZE_Y / 2 + lineHeight / 2) * step;
        int y = drawStart;
        while (y < drawEnd)
        {
            int texY = (int)texPos & (SQUARESIZE - 1);
            texPos += step;
            int color = game->objmap[mapX][mapY]->get_image(game->objmap[mapX][mapY], SOUTH);
            if (side == 1)
                color = (color >> 1) & 8355711;
                
            mypixelput(&game->imgbuffer, x, y, color);
            y++;
        }




        
        if (x == (WINDOWSIZE_X / 2))
        game->select = game->objmap[mapX][mapY];
        
        //int j = 0;
        //int i = drawStart;
        //while (j < drawStart)
        //{
        //    mypixelput(&game->imgbuffer, x, j, game->texture.ceil_color);
        //    j++;
        //}
        //while (i < drawEnd)
        //{
        //    mypixelput(&game->imgbuffer, x, i, ob->get_image(ob, NORTH));
        //    i++;
        //    j++;
        //}
        //// print floor
        //while (j < WINDOWSIZE_Y)
        //{
        //    mypixelput(&game->imgbuffer, x, j, game->texture.floor_color);
        //    j++;
        //}


        
        
        
        
        
        
        //drawVertical(game, x, vec2i(drawStart, drawEnd), game->objmap[mapX][mapY]);
        x++;
    }
}

// sky and floor drawing can be implemented here for better performance
void drawVertical(t_game *game, int x, t_vec2i y, t_object *ob)
{
    int j = 0;
    int i = y.x;

    if (ob == NULL)
        return ;
    if (x == (WINDOWSIZE_X / 2))
        game->select = ob;
    
    // print sky
    while (j < y.x)
    {
        mypixelput(&game->imgbuffer, x, j, game->texture.ceil_color);
        j++;
    }
    while (i < y.y)
    {
        mypixelput(&game->imgbuffer, x, i, ob->get_image(ob, NORTH));
        i++;
        j++;
    }
    // print floor
    while (j < WINDOWSIZE_Y)
    {
        mypixelput(&game->imgbuffer, x, j, game->texture.floor_color);
        j++;
    }
}
