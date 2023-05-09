# include "../../includes/cub3D.h"

void ray_direction(t_raycast *ray, t_game *game, int x)
{
    ray->cameraX = 2 * x / (double)WINDOWSIZE_X - 1;
    ray->rayDirX = game->player.dirX  + game->player.planeX * ray->cameraX;
    ray->rayDirY = game->player.dirY + game->player.planeY * ray->cameraX;
    ray->mapX = (int)game->player.inv_pos.x;
    ray->mapY = (int)game->player.inv_pos.y;
}

void delta_dist(t_raycast *ray)
{
    ray->deltaDistX = (ray->rayDirX == 0) ? 1e30 : fabs(1 / ray->rayDirX);
    ray->deltaDistY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
}

static void hit_wall(t_raycast *ray, t_game *game)
{
    ray->hit = 0;
    ray->block = 0;
    while (ray->hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (ray->x == (WINDOWSIZE_X / 2) && ray->block == 0 && (game->objmap[ray->mapX][ray->mapY]) && \
            (game->objmap[ray->mapX][ray->mapY]->type == DOOR))
        {
            ray->block = 1;
            ray->first_obj_X = ray->mapX;
            ray->first_obj_Y = ray->mapY;
        }
        if (game->objmap[ray->mapX][ray->mapY] && (game->objmap[ray->mapX][ray->mapY]->type == WALL || \
            (game->objmap[ray->mapX][ray->mapY]->type == DOOR && ((t_door*)game->objmap[ray->mapX][ray->mapY])->state == CLOSED)))
            ray->hit = 1;
    }
}

void perp_wall_dist(t_raycast *ray, t_game *game)
{
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (game->player.inv_pos.x - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->player.inv_pos.x) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (game->player.inv_pos.y - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->player.inv_pos.y) * ray->deltaDistY;
    }
    hit_wall(ray, game);
}