/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:53:10 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/23 11:12:53 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	load_pov(t_plinfo *player, float plane_x, float plane_y)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void	load_orientation(t_plinfo *player, int dir_x, int dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

void	define_start_orientation(t_plinfo *player)
{
	if (player->start == NORTH)
	{
		load_orientation(player, -1, 0);
		load_pov(player, 0, 0.66);
	}
	else if (player->start == SOUTH)
	{
		load_orientation(player, 1, 0);
		load_pov(player, 0, -0.66);
	}
	else if (player->start == EAST)
	{
		load_orientation(player, 0, 1);
		load_pov(player, 0.66, 0);
	}
	else if (player->start == WEST)
	{
		load_orientation(player, 0, -1);
		load_pov(player, -0.66, 0);
	}
}
