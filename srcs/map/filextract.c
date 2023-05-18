/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filextract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:26:31 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 20:57:42 by dadoming         ###   ########.fr       */
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
	if (settings == NULL)
	{
		printf("Exiting program...\n");
		close(fd);
		exit(0);
	}
	close(fd);
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
	map_settings->Ntexpath = elmap_get(map_settings->elmap, "NO");
	map_settings->Stexpath = elmap_get(map_settings->elmap, "SO");
	map_settings->Wtexpath = elmap_get(map_settings->elmap, "WE");
	map_settings->Etexpath = elmap_get(map_settings->elmap, "EA");
	map_settings->Floorstr = elmap_get(map_settings->elmap, "F");
	map_settings->Ceilstr = elmap_get(map_settings->elmap, "C");
	if ((map_settings->Ntexpath && map_settings->Stexpath \
			&& map_settings->Wtexpath && map_settings->Etexpath \
			&& map_settings->Floorstr && map_settings->Ceilstr \
			&& map_settings->charmap) == 0)
		free_on_invalid(map_settings);
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
