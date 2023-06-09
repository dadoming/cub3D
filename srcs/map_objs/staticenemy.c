/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staticenemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:32:21 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/23 11:06:02 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	action_staticenemy(t_object **this, t_game *game)
{
	t_staticenemy	*staticenemy;

	staticenemy = (t_staticenemy *)*this;
	if (staticenemy->animation.frames == game->capy_munch.frames)
		staticenemy->animation = game->capy_walk;
	else
		staticenemy->animation = game->capy_munch;
}

t_imgbuffer	get_image_staticenemy(t_staticenemy *this, int dir)
{
	return (this->animation.current_frame->img);
	(void)dir;
}

t_object	*new_staticenemy(t_game *game)
{
	t_staticenemy	*staticenemy;

	staticenemy = ft_calloc(sizeof(t_staticenemy), 1);
	staticenemy->type = STATICENEMY;
	staticenemy->get_image = get_image_staticenemy;
	staticenemy->action = action_staticenemy;
	staticenemy->animation = game->capy_munch;
	return ((t_object *)staticenemy);
}
