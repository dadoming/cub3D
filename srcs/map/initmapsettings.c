/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmapsettings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:00:45 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 01:03:56 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void		init_map_settings_2(t_settings **map_settings);

t_settings	*init_map_settings(int list_size)
{
	t_settings	*map_settings;

	map_settings = malloc(sizeof(t_settings));
	if (!map_settings)
		return (NULL);
	init_map_settings_2(&map_settings);
	if (list_size < ELINFOLIMIT)
	{
		free(map_settings);
		printf("Error: Invalid map content\n");
		return (NULL);
	}
	return (map_settings);
}

static void	init_map_settings_2(t_settings **map_settings)
{
	int	i;

	i = 0;
	(*map_settings)->ceilstr = NULL;
	(*map_settings)->floorstr = NULL;
	(*map_settings)->ntexpath = NULL;
	(*map_settings)->stexpath = NULL;
	(*map_settings)->wtexpath = NULL;
	(*map_settings)->etexpath = NULL;
	(*map_settings)->charmap = NULL;
	while (i < ELINFOLIMIT)
	{
		(*map_settings)->elmap[i].key = NULL;
		(*map_settings)->elmap[i].val = NULL;
		i++;
	}
}
