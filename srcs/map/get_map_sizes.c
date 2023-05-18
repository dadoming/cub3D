/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_sizes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:58:43 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:00:33 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_bottom(char **map, int y, int x);
static int	get_top(char **map, int y, int x);
static int	get_left(char **map, int y, int x);
static int	get_right(char **map, int y, int x);

void	get_maximum_values(t_map_check *maxs, char **map)
{
	maxs->top = get_top(map, 0, 0);
	maxs->bottom = get_bottom(map, ft_mtrxlen((void **) map) - 1, 0);
	maxs->right = get_right(map, 0, 0);
	maxs->left = get_left(map, 0, 0);
}

static int	get_top(char **map, int y, int x)
{
	while (map[y])
	{
		if (map[y][x] == WALL)
			return (y);
		while (map[y][x])
		{
			if (map[y][x] == WALL)
				return (y);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

static int	get_bottom(char **map, int y, int x)
{
	while (y >= 0 && map[y])
	{
		if (map[y][x] == WALL)
			return (y);
		while (map[y][x])
		{
			if (map[y][x] == WALL)
				return (y);
			x++;
		}
		x = 0;
		y--;
	}
	return (0);
}

static int	get_left(char **map, int y, int x)
{
	int	last;

	last = get_right(map, 0, 0);
	while (map[y])
	{
		if (map[y][x] == WALL && x < last)
			last = x;
		while (map[y][x])
		{
			if (map[y][x] == WALL && x < last)
				last = x;
			x++;
		}
		x = 0;
		y++;
	}
	return (last);
}

static int	get_right(char **map, int y, int x)
{
	int	last;

	last = 0;
	while (map[y])
	{
		if (map[y][x] == WALL && x > last)
			last = x;
		while (map[y][x])
		{
			if (map[y][x] == WALL && x > last)
				last = x;
			x++;
		}
		x = 0;
		y++;
	}
	return (last);
}
