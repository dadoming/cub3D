/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgbuffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:58:19 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 23:58:50 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y)
{
	return (y * imgbuffer->line_length + x * (imgbuffer->bits_per_pixel / 8));
}

int	mypixelget(t_imgbuffer *imgbuffer, int x, int y)
{
	int	color;
	int	offset;

	offset = imgbufferoffset(imgbuffer, x, y);
	color = *(int *)(imgbuffer->addr + offset);
	return (color);
}
