/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_on_invalid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:57:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:10:22 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	free_on_invalid(t_settings *settings)
{
	free(settings->Ntexpath);
	free(settings->Stexpath);
	free(settings->Wtexpath);
	free(settings->Etexpath);
	free(settings->Floorstr);
	free(settings->Ceilstr);
	charmap_free(settings->charmap);
	elmap_free(settings->elmap);
	free(settings);
	printf("Error: Invalid map info\nExiting program...\n");
	exit(0);
}
