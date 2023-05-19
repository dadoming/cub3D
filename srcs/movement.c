/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:10:19 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 00:29:36 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	collision(t_game *game, int x, int y)
{
	t_object	*obj;

	obj = game->objmap[x][y];
	if (obj == NULL || obj->type == 0)
		return (1);
	if (obj->type == DOOR && ((t_door *) obj)->state)
		return (1);
	return (0);
}

void	press_forward(t_game *game)
{
	if (collision(game, floor(game->player.inv_pos.x + \
		game->player.dir_x * MOVESPEED), floor(game->player.inv_pos.y)))
			game->player.inv_pos.x += game->player.dir_x * MOVESPEED;
	if (collision(game, floor(game->player.inv_pos.x), \
		floor(game->player.inv_pos.y + game->player.dir_y * MOVESPEED)))
			game->player.inv_pos.y += game->player.dir_y * MOVESPEED;
}

void	press_back(t_game *game)
{
	if (collision(game, floor(game->player.inv_pos.x - game->player.dir_x \
		* MOVESPEED), floor(game->player.inv_pos.y)))
		game->player.inv_pos.x -= game->player.dir_x * MOVESPEED;
	if (collision(game, floor(game->player.inv_pos.x), \
		floor(game->player.inv_pos.y - game->player.dir_y * MOVESPEED)))
		game->player.inv_pos.y -= game->player.dir_y * MOVESPEED;
}

void	press_left(t_game *game)
{
	if (collision(game, floor(game->player.inv_pos.x - game->player.plane_x \
		* MOVESPEED), floor(game->player.inv_pos.y)))
		game->player.inv_pos.x -= game->player.plane_x * MOVESPEED;
	if (collision(game, floor(game->player.inv_pos.x), \
		floor(game->player.inv_pos.y - game->player.plane_y * MOVESPEED)))
		game->player.inv_pos.y -= game->player.plane_y * MOVESPEED;
}

void	press_right(t_game *game)
{
	if (collision(game, floor(game->player.inv_pos.x + game->player.plane_x \
		* MOVESPEED), floor(game->player.inv_pos.y)))
		game->player.inv_pos.x += game->player.plane_x * MOVESPEED;
	if (collision(game, floor(game->player.inv_pos.x), \
		floor(game->player.inv_pos.y + game->player.plane_y * MOVESPEED)))
		game->player.inv_pos.y += game->player.plane_y * MOVESPEED;
}
