/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:31:03 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 22:36:08 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	line_height(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perpWallDist = (ray->side_dist_y - ray->delta_dist_y);
	ray->lineHeight = (int)(WINDOWSIZE_Y / ray->perpWallDist);
}

void	get_draw_start_end(t_raycast *ray)
{
	ray->drawStart = -ray->lineHeight / 2 + WINDOWSIZE_Y / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + WINDOWSIZE_Y / 2;
	if (ray->drawEnd >= WINDOWSIZE_Y)
		ray->drawEnd = WINDOWSIZE_Y - 1;
}
