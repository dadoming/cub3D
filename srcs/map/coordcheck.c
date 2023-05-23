/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:12:37 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/23 11:12:48 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	coordcheck(t_game *game, int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	else if (x >= WINDOWSIZE_X || y >= WINDOWSIZE_Y)
		return (0);
	else if (y >= game->mapsize.y)
		return (0);
	else if (x >= game->mapsize.x)
		return (0);
	else
		return (game->charmap[y][x]);
}

char	coordcheck_prop(t_game *game, int x, int y)
{
	return (coordcheck(game, x / SQUARESIZE, y / SQUARESIZE));
}
