/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_maps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:16:28 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:52:22 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/menu.h"

static void		remove_invalid_maps(t_map_list **map_list);

t_map_list	*get_available_maps(void)
{
	t_map_list	*map_list;

	map_list = load_map_list();
	if (!map_list)
		return (NULL);
	remove_invalid_maps(&map_list);
	if (!map_list)
	{
		printf("Error: no maps found!\n");
		return (NULL);
	}
	return (map_list);
}

t_map_list	*load_map_list(void)
{
	DIR				*dir;
	struct dirent	*entry;
	t_map_list		*map_list;

	dir = opendir("./maps");
	if (!dir)
	{
		printf("Error: could not open maps directory!\n");
		return (NULL);
	}
	map_list = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			printf("Found map: %s\n", entry->d_name);
			insert_at_end(&map_list, create_node(ft_strdup(entry->d_name)));
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (map_list);
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

static void	remove_invalid_maps(t_map_list **map_list)
{
	t_map_list	*tmp;
	t_map_list	*next;

	if (!*map_list)
		return ;
	tmp = *map_list;
	while (tmp != (*map_list)->prev)
	{
		printf("Checking map: %s\n", tmp->name);
		next = tmp->next;
		if (check_valid_filename(tmp->name) == 0)
		{
			printf("Removing invalid map: %s\n", tmp->name);
			delete_node(map_list, tmp);
		}
		tmp = next;
	}
	if (!check_valid_filename((*map_list)->name))
	{
		printf("Removing invalid map: %s\n", (*map_list)->name);
		delete_node(map_list, *map_list);
	}
}
