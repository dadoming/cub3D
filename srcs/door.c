/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:55:48 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 18:55:18 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	action_door(t_object **this, t_game *game)
{
	t_door	*door;
	float	dist;

	door = (t_door *)(*this);
	dist = sqrt(pow(game->player.pos.x - door->x, 2) \
		+ pow(game->player.pos.y - door->y, 2));
	if (dist <= 2)
		door->state = !door->state;
}

static t_imgbuffer	get_image_door(t_door *this, int dir)
{
	return (*this->texture_door_closed);
	(void)dir;
}

t_object	*new_door(int x, int y, t_game *game)
{
	t_door	*door;

	door = ft_calloc(sizeof(t_door), 1);
	door->type = DOOR;
	door->get_image = get_image_door;
	door->action = action_door;
	door->x = x;
	door->y = y;
	door->state = 0;
	door->texture_door_closed = &game->texture_door;
	return ((t_object *)door);
}
