/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:41:37 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 00:42:00 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_vec2f	vec2f(float x, float y)
{
	t_vec2f	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}

t_vec2i	vec2i(int x, int y)
{
	t_vec2i	tmp;

	tmp.x = x;
	tmp.y = y;
	return (tmp);
}
