/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_orientation2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:02:51 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:05:16 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	player_pos(t_plinfo *player, int x, int y)
{
	player->pos.x = (float)x;
	player->pos.y = (float)y;
}
