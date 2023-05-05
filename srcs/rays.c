# include "../includes/cub3D.h"

void drawVertical(t_game *game, int x, t_vec2i y, t_object *ob);

void ft_swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void extract_texture_pixels(t_imgbuffer *texture, int *pixels)
{
    int x, y;
    int color;

    for (y = 0; y < texture->height; y++)
    {
        for (x = 0; x < texture->width; x++)
        {
            // extract color value at (x, y) in RGB format
            color = *(int *)(texture->addr + (y * texture->line_length) + (x * (texture->bits_per_pixel / 8)));

            // store color value in pixels array
            pixels[(y * texture->width) + x] = color;
        }
    }
}

void draw_transparent_square(void *mlx_ptr, void *win_ptr, int x, int y, int size, int alpha)
{
    unsigned int color = (alpha << 24) | 0xFFFFFF; // 32-bit color with alpha channel
    int i, j;

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            mlx_pixel_put(mlx_ptr, win_ptr, x + i, y + j, color);
        }
    }
}

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
        int texture_pixels[SQUARESIZE * SQUARESIZE];
        t_imgbuffer img;
        if (side == 0 && rayDirX > 0)
            img = game->objmap[mapX][mapY]->get_image(game->objmap[mapX][mapY], WEST);
        else if (side == 0 && rayDirX < 0)
            img = game->objmap[mapX][mapY]->get_image(game->objmap[mapX][mapY], EAST);
        else if (side == 1 && rayDirY > 0)
            img = game->objmap[mapX][mapY]->get_image(game->objmap[mapX][mapY], SOUTH);
        else if (side == 1 && rayDirY < 0)
            img = game->objmap[mapX][mapY]->get_image(game->objmap[mapX][mapY], NORTH);
        if (game->objmap[mapX][mapY]->type == DOOR && ((t_door *)game->objmap[mapX][mapY])->state == 0)
            img = game->objmap[mapX][mapY]->get_image((t_object*)(game->objmap[mapX][mapY]), 0);
        else if (game->objmap[mapX][mapY]->type == DOOR && ((t_door *)game->objmap[mapX][mapY])->state == 1)
            img = game->objmap[mapX][mapY]->get_image((t_object*)(game->objmap[mapX][mapY]), 1);
        extract_texture_pixels(&img, texture_pixels);

        
        // improve performance in texture loading
        for(size_t x = 0; x < SQUARESIZE; x++)
            for(size_t y = 0; y < x; y++)
                ft_swap(&texture_pixels[SQUARESIZE * y + x], &texture_pixels[SQUARESIZE * x + y]);
        
        
        
        int j = 0;
        while (j < drawStart)
        {
            mypixelput(&game->imgbuffer, x, j, game->ceil_color);
            j++;
        }
        while (y < drawEnd)
        {
            int texY = (int)texPos & (SQUARESIZE - 1);
            texPos += step;
            int color = texture_pixels[SQUARESIZE * texY + texX];
            if (side == 1)
                color = (color >> 1) & 8355711;
                
            mypixelput(&game->imgbuffer, x, y, color);
            y++;
            j++;
        }
        while (j < WINDOWSIZE_Y)
        {
            mypixelput(&game->imgbuffer, x, j, game->floor_color);
            j++;
        }
        if (x == (WINDOWSIZE_X / 2))
        game->select = game->objmap[mapX][mapY];
          
        //drawVertical(game, x, vec2i(drawStart, drawEnd), game->objmap[mapX][mapY]);
        x++;
    }
}

// sky and floor drawing can be implemented here for better performance
//void drawVertical(t_game *game, int x, t_vec2i y, t_object *ob)
//{
//    int j = 0;
//    int i = y.x;
//
//    if (ob == NULL)
//        return ;
//    if (x == (WINDOWSIZE_X / 2))
//        game->select = ob;
//    
//    // print sky
//    while (j < y.x)
//    {
//        mypixelput(&game->imgbuffer, x, j, game->texture.ceil_color);
//        j++;
//    }
//    while (i < y.y)
//    {
//        mypixelput(&game->imgbuffer, x, i, ob->get_image(ob, NORTH));
//        i++;
//        j++;
//    }
//    // print floor
//    while (j < WINDOWSIZE_Y)
//    {
//        mypixelput(&game->imgbuffer, x, j, game->floor_color);
//        j++;
//    }
//}
//