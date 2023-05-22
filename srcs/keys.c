/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:29:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 17:12:07 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	rotate_direction(t_game *game, double angle_x, double angle_y)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * \
		angle_x - game->player.dir_y * angle_y;
	game->player.dir_y = old_dir_x * angle_y + game->player.dir_y * angle_x;
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * \
		angle_x - game->player.plane_y * angle_y;
	game->player.plane_y = old_plane_x * angle_y + \
		game->player.plane_y * angle_x;
}

void	wasd(t_game *game, int key)
{
	if (key == W)
		press_forward(game);
	else if (key == A)
	{
		if (game->mouse_selected)
			press_left(game);
		else
			rotate_direction(game, cos(ROTATESPEED), sin(ROTATESPEED));
	}
	else if (key == S)
		press_back(game);
	else if (key == D)
	{
		if (game->mouse_selected)
			press_right(game);
		else
			rotate_direction(game, cos(-ROTATESPEED), sin(-ROTATESPEED));
	}
}

int	key_event(int key, t_game *game)
{
	if (key == ESC)
		close_game(game);
	wasd(game, key);
	if (key == SPACE && (*(game->select)) && (*(game->select))->action)
		(*(game->select))->action(game->select, game);
	else if (key == CTRL)
		game->minimap_toggle = !game->minimap_toggle;
	else if (key == SHIFT)
		game->player_shoot.trigger = 1;
	return (0);
}
