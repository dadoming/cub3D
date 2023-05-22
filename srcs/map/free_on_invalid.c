/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_invalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaria-d <amaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:57:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 17:26:30 by amaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_on_invalid(t_settings *settings)
{
	free(settings->ntexpath);
	free(settings->stexpath);
	free(settings->wtexpath);
	free(settings->etexpath);
	free(settings->floorstr);
	free(settings->ceilstr);
	charmap_free(&settings->charmap);
	elmap_free(settings->elmap);
	free(settings);
	printf("Error: Invalid map info\nExiting program...\n");
	exit(0);
}

void	free_paths(t_settings *map_settings)
{
	free(map_settings->ntexpath);
	free(map_settings->stexpath);
	free(map_settings->wtexpath);
	free(map_settings->etexpath);
	free(map_settings->ceilstr);
	free(map_settings->floorstr);
	free(map_settings);
}

void	free_map_settings_no_exit(t_settings *settings)
{
	free(settings->ntexpath);
	free(settings->stexpath);
	free(settings->wtexpath);
	free(settings->etexpath);
	free(settings->floorstr);
	free(settings->ceilstr);
	elmap_free(settings->elmap);
	free(settings);
}
