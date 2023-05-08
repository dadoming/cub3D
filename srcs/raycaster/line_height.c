#include "../../includes/cub3D.h"

void line_height(t_raycast *ray)
{
    if (ray->side == 0)
        ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
        ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
    ray->lineHeight = (int)(WINDOWSIZE_Y / ray->perpWallDist);
}

void get_draw_start_end(t_raycast *ray)
{
    ray->drawStart = -ray->lineHeight / 2 + WINDOWSIZE_Y / 2;
    if (ray->drawStart < 0)
        ray->drawStart = 0;
    ray->drawEnd = ray->lineHeight / 2 + WINDOWSIZE_Y / 2;
    if (ray->drawEnd >= WINDOWSIZE_Y)
        ray->drawEnd = WINDOWSIZE_Y - 1;
}
