/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:29:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 19:20:06 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_game(game);
	wasd(game, key, 1);
	if (key == SPACE && (*(game->select)) && (*(game->select))->action)
		(*(game->select))->action(game->select, game);
	else if (key == CTRL)
		game->minimap_toggle = !game->minimap_toggle;
	else if (key == SHIFT)
		game->player_shoot.trigger = 1;
	return (0);
}

int	key_release(int key, t_game *game)
{
	wasd(game, key, 0);
	return (0);
}

void	keys_treatment(t_game *game)
{
	mlx_hook(game->win, 02, 1L << 0, key_press, game);
	mlx_hook(game->win, 03, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 1L << 2, x_close_window, game);
	if (game->mouse_selected)
	{
		mlx_mouse_move(game->mlx, game->win, \
			WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
		mlx_mouse_hide(game->mlx, game->win);
		mlx_hook(game->win, 6, 1L << 6, mousemove_capture, game);
		mlx_hook(game->win, 4, 1L << 6, mousedown_capture, game);
	}
}

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

void	wasd(t_game *game, int key, int setter)
{
	if (key == W)
		game->movement.w = setter;
	else if (key == A)
		game->movement.a = setter;
	else if (key == S)
		game->movement.s = setter;
	else if (key == D)
		game->movement.d = setter;
}
