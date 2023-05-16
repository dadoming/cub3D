# include "../../includes/cub3D.h"

static void extract_texture_pixels(t_imgbuffer *texture, int *pixels)
{
    int x, y;
    int color;

    for (y = 0; y < texture->height; y++)
    {
        for (x = 0; x < texture->width; x++)
        {
            if (y * texture->width + x > SQUARESIZE*SQUARESIZE)
            {
                printf("Extract texture error\n");
                return;
            }
            // extract color value at (x, y) in RGB format
            // color = *(int *)(texture->addr + (y * texture->line_length) + (x * (texture->bits_per_pixel / 8)));
            color = mypixelget(texture, x, y);
            if ((color & 0x00FFFFFF) != 0) // if color is full transparent
                // store color value in pixels array
                pixels[(y * texture->width) + x] = color;
        }
    }
}

void load_buffer_array(t_raycast *ray, t_game *game)
{
    t_imgbuffer img;

         if (game->objmap[ray->mapX][ray->mapY]->type == DYNAMITE)
    {
        img = game->objmap[ray->mapX][ray->mapY]->get_image(game->objmap[ray->mapX][ray->mapY], 0);
    }
    else if (ray->side == 0 && ray->rayDirX > 0 && (game->objmap[ray->mapX][ray->mapY]->type != DOOR))
        img = game->objmap[ray->mapX][ray->mapY]->get_image(game->objmap[ray->mapX][ray->mapY], WEST);
    else if (ray->side == 0 && ray->rayDirX < 0 && (game->objmap[ray->mapX][ray->mapY]->type != DOOR))
        img = game->objmap[ray->mapX][ray->mapY]->get_image(game->objmap[ray->mapX][ray->mapY], EAST);
    else if (ray->side == 1 && ray->rayDirY > 0 && (game->objmap[ray->mapX][ray->mapY]->type != DOOR))
        img = game->objmap[ray->mapX][ray->mapY]->get_image(game->objmap[ray->mapX][ray->mapY], SOUTH);
    else if (ray->side == 1 && ray->rayDirY < 0 && (game->objmap[ray->mapX][ray->mapY]->type != DOOR))
        img = game->objmap[ray->mapX][ray->mapY]->get_image(game->objmap[ray->mapX][ray->mapY], NORTH);
    else if (game->objmap[ray->mapX][ray->mapY]->type == DOOR && ((t_door *)game->objmap[ray->mapX][ray->mapY])->state == 0)
        img = game->objmap[ray->mapX][ray->mapY]->get_image((t_object*)(game->objmap[ray->mapX][ray->mapY]), 0);
    else
        img = game->texture_transparent;
    extract_texture_pixels(&img, ray->texture_pixels);
}

void wall_texture_position(t_raycast *ray, t_game *game)
{
    if (ray->side == 0)
        ray->wallX = game->player.inv_pos.y + ray->perpWallDist * ray->rayDirY;
    else
        ray->wallX = game->player.inv_pos.x + ray->perpWallDist * ray->rayDirX;
    ray->wallX -= floor(ray->wallX);
    ray->texX = (int)(ray->wallX * (double)SQUARESIZE);
    if (ray->side == 0 && ray->rayDirX > 0)
        ray->texX = SQUARESIZE - ray->texX - 1;
    if (ray->side == 1 && ray->rayDirY < 0)
        ray->texX = SQUARESIZE - ray->texX - 1;
    ray->step = 1.0 * SQUARESIZE / ray->lineHeight;
    ray->texPos = (ray->drawStart - WINDOWSIZE_Y / 2 + ray->lineHeight / 2) * ray->step;
    load_buffer_array(ray, game);   
}

void draw_vertical_stripe(t_game *game, t_raycast *ray)
{
    int y;
    int j;
    int texY;
    int color;

    y = ray->drawStart;
    j = 0;
    while (j < ray->drawStart)
    {
        mypixelput(&game->imgbuffer, ray->x, j, game->ceil_color);
        j++;
    }
    while (y < ray->drawEnd)
    {
        texY = (int)ray->texPos & (SQUARESIZE - 1);
        ray->texPos += ray->step;
        color = ray->texture_pixels[SQUARESIZE * texY + ray->texX];
        if (ray->side == 1)
            color = (color >> 1) & 8355711;
        mypixelput(&game->imgbuffer, ray->x, y, color);
        y++;
        j++;
    }
    while (j < WINDOWSIZE_Y)
    {
        mypixelput(&game->imgbuffer, ray->x, j, game->floor_color);
        j++;
    }
}
