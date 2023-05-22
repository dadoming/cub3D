/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_borders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:43:55 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 15:16:43 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	fill_map(char **map, t_map_check maxs, char **new_map);

char	**cut_and_define_border(char **map)
{
	char			**new_map;
	t_map_check		maxs;

	get_maximum_values(&maxs, map);
	if (maxs.bottom - maxs.top < 3 && maxs.right - maxs.left < 3)
	{
		printf("Map is too small\n");
		charmap_free(&map);
		return (NULL);
	}
	new_map = malloc(sizeof(char *) * (maxs.bottom - maxs.top + 3 + 1));
	fill_map(map, maxs, new_map);
	charmap_free(&map);
	return (new_map);
}

static void	fill_map(char **map, t_map_check maxs, char **new_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < maxs.bottom - maxs.top + 2 + 1)
	{
		j = 0;
		new_map[i] = malloc(sizeof(char) * (maxs.right - maxs.left + 2 + 2));
		while (j < maxs.right - maxs.left + 2 + 1)
		{
			if (i == 0 || j == 0 || j == maxs.right - \
				maxs.left + 2 || i == maxs.bottom - maxs.top + 2)
				new_map[i][j] = '2';
			else if ((j + maxs.left - 1 < (int)ft_strlen(\
				map[i + maxs.top - 1])) && ft_charinside(\
				map[i + maxs.top - 1][j + maxs.left - 1], VALIDSTRING))
				new_map[i][j] = map[i + maxs.top - 1][j + maxs.left - 1];
			else
				new_map[i][j] = '2';
			j++;
		}
		new_map[i][j] = '\0';
		i++;
	}
	new_map[i] = NULL;
}
