/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   residualcleaning.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:08:42 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 01:03:59 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_evaluation(t_settings **map_settings)
{
	printf("Cleaning Settings.\n");
	elmap_free((*map_settings)->elmap);
	if ((*map_settings)->charmap)
		charmap_free((*map_settings)->charmap);
	if ((*map_settings)->ntexpath)
		free((*map_settings)->ntexpath);
	if ((*map_settings)->stexpath)
		free((*map_settings)->stexpath);
	if ((*map_settings)->wtexpath)
		free((*map_settings)->wtexpath);
	if ((*map_settings)->etexpath)
		free((*map_settings)->etexpath);
	if ((*map_settings)->floorstr)
		free((*map_settings)->floorstr);
	if ((*map_settings)->ceilstr)
		free((*map_settings)->ceilstr);
	free(*map_settings);
}

void	free_list(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->content)
			free(tmp->content);
		tmp->content = NULL;
		(*list) = (*list)->next;
		free(tmp);
		tmp = *list;
	}
}

int	charmap_free(char **charmap)
{
	size_t	i;

	if (!charmap)
		return (0);
	i = 0;
	while (charmap[i] != NULL)
	{
		free(charmap[i]);
		charmap[i] = NULL;
		i++;
	}
	free(charmap);
	charmap = NULL;
	return (1);
}

void	elmap_free(t_elinfo *elmap)
{
	int	i;

	i = 0;
	while (i < ELINFOLIMIT)
	{
		if (elmap[i].key != NULL)
			free(elmap[i].key);
        elmap[i].key = NULL;
		if (elmap[i].val != NULL)
			free(elmap[i].val);
        elmap[i].val = NULL;
        i++;
	}
    elmap = NULL;
}
