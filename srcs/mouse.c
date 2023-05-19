/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:08:20 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 00:09:25 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mousemove_capture(int x, int y, void *param)
{
	t_game	*game;

	game = param;
	if (x > WINDOWSIZE_X / 2)
		rotate_direction(game, cos(-ROTATESPEED / ROTDIVIDER), \
		sin(-ROTATESPEED / ROTDIVIDER));
	if (x < WINDOWSIZE_X / 2)
		rotate_direction(game, cos(ROTATESPEED / ROTDIVIDER), \
		sin(ROTATESPEED / ROTDIVIDER));
	mlx_mouse_move(game->mlx, game->win, WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
	return (1);
	(void)y;
}

int	mousedown_capture(int button, int x, int y, void *param)
{
	t_game	*game;

	game = param;
	if (button == 1)
		game->player_shoot.trigger = 1;
	else if (button == 3)
	{
		if ((*(game->select)) && (*(game->select))->action)
			(*(game->select))->action(game->select, game);
	}
	else if (button == 4)
		game->minimap_toggle = 0;
	else if (button == 5)
		game->minimap_toggle = 1;
	return (1);
	(void)x;
	(void)y;
}