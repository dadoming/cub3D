/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filextract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:26:31 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 01:03:51 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static char		*elmap_get(t_elinfo *elmap, char *elmapKey);
t_settings		*settings_set(t_settings *map_settings);
static int		check_valid_filename(const char *str);
static void		load_map_file(t_start_values *ret, int *fd);

int	file_extract(t_start_values ret)
{
	int			fd;
	t_settings	*settings;

	load_map_file(&ret, &fd);
	settings = read_settings(fd);
	close(fd);
	if (settings == NULL)
	{
		printf("Exiting program...\n");
		exit(0);
	}
	settings = settings_set(settings);
	return (prep_game(settings, prepare_map(settings), ret.mouse_selected));
}

static void	load_map_file(t_start_values *ret, int *fd)
{
	printf("----------------------------------------\n");
	printf("Extracting content from: %s\n", ret->map_name);
	if (check_valid_filename(ret->map_name) == 0)
	{
		printf("Invalid map filename!\nExiting program...\n");
		free(ret->map_name);
		exit(0);
	}
	*fd = open(ret->map_name, O_RDONLY);
	if (*fd <= 0)
	{
		printf("Could not open file!\nExiting program...\n");
		free(ret->map_name);
		exit(0);
	}
	free(ret->map_name);
}

t_settings	*settings_set(t_settings *map_settings)
{
	int	i;

	i = 0;
	map_settings->ntexpath = elmap_get(map_settings->elmap, "NO");
	map_settings->stexpath = elmap_get(map_settings->elmap, "SO");
	map_settings->wtexpath = elmap_get(map_settings->elmap, "WE");
	map_settings->etexpath = elmap_get(map_settings->elmap, "EA");
	map_settings->floorstr = elmap_get(map_settings->elmap, "F");
	map_settings->ceilstr = elmap_get(map_settings->elmap, "C");
	if ((map_settings->ntexpath && map_settings->stexpath \
			&& map_settings->wtexpath && map_settings->etexpath \
			&& map_settings->floorstr && map_settings->ceilstr \
			&& map_settings->charmap) == 0)
		{
			printf("Duplicate has been found\n");
			free_on_invalid(map_settings);
		}
	while (i < ELINFOLIMIT)
	{
		free(map_settings->elmap[i].key);
		map_settings->elmap[i].key = NULL;
		free(map_settings->elmap[i].val);
		map_settings->elmap[i].val = NULL;
		i++;
	}
	return (map_settings);
}

static char	*elmap_get(t_elinfo *elmap, char *elmapKey)
{
	size_t	i;

	i = 0;
	while (i < ELINFOLIMIT)
	{
		if (elmap[i].key != NULL && ft_strcmp(elmapKey, elmap[i].key) == 0)
			return (ft_strdup(elmap[i].val));
		i++;
	}
	return (NULL);
}

static int	check_valid_filename(const char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] != '.')
		i--;
	str = str + i;
	if (i < 0)
	{
		return (0);
	}
	return (ft_strncmp(str, ".cub", 5) == 0);
}
