/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:32:57 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 14:47:26 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	norm_helper_iter(t_game *game, t_microseconds now, int j, int i)
{
	if (game->objmap[j][i]->type == STATICENEMY)
	{
		update_anim(&((t_staticenemy *)game->objmap[j][i])->animation, now);
		((t_staticenemy *)game->objmap[j][i])->animation.trigger = 1;
	}
}

void	objiter(t_game *game, t_microseconds now)
{
	int			j;
	int			i;

	j = 0;
	while (game->charmap[++j])
	{
		i = 0;
		while (game->charmap[j][++i])
		{
			if (game->objmap[j][i])
			{
				norm_helper_iter(game, now, j, i);
			}
		}
	}
}

void	update(t_game *game, t_microseconds tmstmpnow)
{
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	objiter(game, tmstmpnow);
	update_anim(&game->player_shoot, tmstmpnow);
	draw_weapon(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
}
