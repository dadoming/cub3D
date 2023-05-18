/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:13:21 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 23:28:43 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char	*trim_spaces(char **rgb, int i)
{
	char	*str;

	str = ft_strtrim(rgb[i], " ");
	if (str == NULL)
	{
		i = 0;
		while (rgb[i])
			free(rgb[i++]);
		free(rgb);
		return (NULL);
	}
	return (str);
}

int	check_only_numbers(char *str, char **rgb, int i)
{
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			i = 0;
			while (rgb[i])
				free(rgb[i++]);
			free(rgb);
			free(str);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	atoi_this(char *str, char **rgb, int i, int *rgbi)
{
	rgbi[i] = ft_atoi(str);
	free(str);
	if (rgbi[i] < 0 || rgbi[i] > 255)
	{
		i = 0;
		while (rgb[i])
			free(rgb[i++]);
		free(rgb);
		return (-1);
	}
	return (rgbi[i]);
}

int	rgb_norm(char *str, char **rgb, int *rgbi, int i)
{
	str = trim_spaces(rgb, i);
	if (str == NULL)
		return (-1);
	if (check_only_numbers(str, rgb, i) == -1)
		return (-1);
	rgbi[i] = atoi_this(str, rgb, i, rgbi);
	if (rgbi[i] == -1)
		return (-1);
	return (0);
}
