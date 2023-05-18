/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:31:35 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 22:36:16 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ray_direction(t_raycast *ray, t_game *game, int x)
{
	ray->cameraX = 2 * x / (double)WINDOWSIZE_X - 1;
	ray->ray_dir_x = game->player.dirX  + game->player.planeX * ray->cameraX;
	ray->ray_dir_y = game->player.dirY + game->player.planeY * ray->cameraX;
	ray->mapX = (int)game->player.inv_pos.x;
	ray->mapY = (int)game->player.inv_pos.y;
}

void delta_dist(t_raycast *ray)
{
    ray->delta_dist_x = (ray->ray_dir_x == 0) ? 1e30 : fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = (ray->ray_dir_y == 0) ? 1e30 : fabs(1 / ray->ray_dir_y);
}

static void hit_wall(t_raycast *ray, t_game *game)
{
    ray->hit = 0;
    ray->block = 0;
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (ray->x == (WINDOWSIZE_X / 2) && ray->block == 0 && (game->objmap[ray->mapX][ray->mapY]))
        {
            ray->block = 1;
            ray->first_obj_X = ray->mapX;
            ray->first_obj_Y = ray->mapY;
        }
        if (game->objmap[ray->mapX][ray->mapY] && (game->objmap[ray->mapX][ray->mapY]->type == WALL || \
            (game->objmap[ray->mapX][ray->mapY]->type == DOOR && ((t_door*)game->objmap[ray->mapX][ray->mapY])->state == CLOSED) || \
            (game->objmap[ray->mapX][ray->mapY]->type == DYNAMITE)|| (game->objmap[ray->mapX][ray->mapY]->type == STATICENEMY)))
            ray->hit = 1;
    }
}

void perp_wall_dist(t_raycast *ray, t_game *game)
{
    if (ray->ray_dir_x < 0)
    {
        ray->stepX = -1;
        ray->side_dist_x = (game->player.inv_pos.x - ray->mapX) * ray->delta_dist_x;
    }
    else
    {
        ray->stepX = 1;
        ray->side_dist_x = (ray->mapX + 1.0 - game->player.inv_pos.x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->stepY = -1;
        ray->side_dist_y = (game->player.inv_pos.y - ray->mapY) * ray->delta_dist_y;
    }
    else
    {
        ray->stepY = 1;
        ray->side_dist_y = (ray->mapY + 1.0 - game->player.inv_pos.y) * ray->delta_dist_y;
    }
    hit_wall(ray, game);
}