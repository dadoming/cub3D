/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_height.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:31:03 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 22:44:29 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	line_height(t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WINDOWSIZE_Y / ray->perp_wall_dist);
}

void	get_draw_start_end(t_raycast *ray)
{
	ray->draw_start = -ray->line_height / 2 + WINDOWSIZE_Y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WINDOWSIZE_Y / 2;
	if (ray->draw_end >= WINDOWSIZE_Y)
		ray->draw_end = WINDOWSIZE_Y - 1;
}
