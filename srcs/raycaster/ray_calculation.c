/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:31:35 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 23:52:18 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	ray_direction(t_raycast *ray, t_game *game, int x)
{
	ray->camera_x = 2 * x / (double)WINDOWSIZE_X - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->map_x = (int)game->player.inv_pos.x;
	ray->map_y = (int)game->player.inv_pos.y;
}

void	delta_dist(t_raycast *ray)
{
	if (ray->ray_dir_x == 0)
	{
		ray->delta_dist_x = 1e30;
	}
	else
	{
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	}
	if (ray->ray_dir_y == 0)
	{
		ray->delta_dist_y = 1e30;
	}
	else
	{
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	}
}

static void	ray_hit_the_wall(t_game *game, t_raycast *ray)
{
	if (ray->x == (WINDOWSIZE_X / 2) && ray->block == 0 && \
		(game->objmap[ray->map_x][ray->map_y]))
	{
		ray->block = 1;
		ray->first_obj_x = ray->map_x;
		ray->first_obj_y = ray->map_y;
	}
	if (game->objmap[ray->map_x][ray->map_y] && (game->objmap \
		[ray->map_x][ray->map_y]->type == WALL || (game->objmap \
		[ray->map_x][ray->map_y]->type == DOOR && ((t_door *) \
		game->objmap[ray->map_x][ray->map_y])->state == CLOSED) || \
		(game->objmap[ray->map_x][ray->map_y]->type == STATICENEMY)))
		ray->hit = 1;
}

static void	hit_wall(t_raycast *ray, t_game *game)
{
	ray->hit = 0;
	ray->block = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		ray_hit_the_wall(game, ray);
	}
}

void	perp_wall_dist(t_raycast *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.inv_pos.x - ray->map_x) \
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.inv_pos.x) \
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.inv_pos.y - ray->map_y) \
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.inv_pos.y) \
			* ray->delta_dist_y;
	}
	hit_wall(ray, game);
}
