/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_convert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:01:18 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 23:28:15 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

char	**rgb_split(char *value)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(value, ',');
	if (rgb == NULL)
		return (NULL);
	if (ft_mtrxlen((void **)rgb) != 3)
	{
		printf("Error\nInvalid RGB input\n");
		while (rgb[i])
			free(rgb[i++]);
		free(rgb);
		return (NULL);
	}
	return (rgb);
}

int	load_rgb(char *value)
{
	char	**rgb;
	char	*str;
	int		rgbi[3];
	int		i;

	str = NULL;
	rgb = rgb_split(value);
	if (rgb == NULL)
		return (-1);
	i = 0;
	while (rgb[i])
	{
		if (rgb_norm(str, rgb, rgbi, i) == -1)
			return (-1);
		i++;
	}
	i = 0;
	while (rgb[i])
		free(rgb[i++]);
	free(rgb);
	return (rgbtocolor(rgbi[0], rgbi[1], rgbi[2]));
}
