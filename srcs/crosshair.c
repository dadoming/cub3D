/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:28 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 23:55:35 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_crosshair(t_game *game, int size, int color)
{
	int		center_x;
	int		center_y;
	t_vec2i	pos;

	center_x = WINDOWSIZE_X / 2;
	center_y = WINDOWSIZE_Y / 2;
	pos.x = center_x - size;
	pos.y = center_y;
	horline(game, pos, size * 2 + 1, color);
	pos.x = center_x;
	pos.y = center_y - size;
	verline(game, pos, size * 2 + 1, color);
}
