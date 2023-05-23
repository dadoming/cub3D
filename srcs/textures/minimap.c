/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:03:21 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/23 11:13:11 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	norm_help(t_game *game, t_vec2i pixeldraw, int x, int y)
{
	if (coordcheck(game, x, y) == WALL)
		pixsquare(game, pixeldraw, MINIMAPSCALE, 0x00D27D2D);
	else if (coordcheck(game, x, y) == DOOR)
		pixsquare(game, pixeldraw, MINIMAPSCALE, 0x00FFD700);
	else if (coordcheck(game, x, y) == STATICENEMY)
		pixsquare(game, pixeldraw, MINIMAPSCALE, 0x00AAD300);
	else
		pixsquare(game, pixeldraw, MINIMAPSCALE, rgbtocolor(255, 0, 0));
}

void	minimap_show(t_game *game)
{
	float	y;
	float	x;
	int		pixeldrawx;
	int		pixeldrawy;

	pixeldrawy = 0;
	y = game->player.pos.y - 3.5;
	while (y < game->player.pos.y + 3.5)
	{
		pixeldrawx = 0;
		x = game->player.pos.x - 3.5;
		while (x < game->player.pos.x + 3.5)
		{
			norm_help(game, vec2i(pixeldrawx, pixeldrawy), x, y);
			x += 0.1;
			pixeldrawx += MINIMAPSCALE;
		}
		y += 0.1;
		pixeldrawy += MINIMAPSCALE;
	}
}

void	draw_minimap(t_game *game)
{
	t_vec2i	vec;

	vec.x = game->player.pos.x;
	vec.y = game->player.pos.y;
	minimap_show(game);
	pixsquare(game, vec2i(35 * MINIMAPSCALE, 35 * MINIMAPSCALE), 3, 0);
	game->player.pos.x = vec.x;
	game->player.pos.y = vec.y;
}
