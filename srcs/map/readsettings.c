/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readsettings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:26 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:08:36 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_list		*read_file(int fd);
void		evaluate_settings(t_list *file_list, t_settings **map_settings);
void		load_elinfo(t_elinfo **map_settings, char *file_line, \
	int i, int option);

t_settings	*read_settings(int openfd)
{
	t_list		*file_list;
	t_settings	*map_settings;
	int			list_size;

	file_list = read_file(openfd);
	if (file_list == NULL)
	{
		printf("Error: File is empty\n");
		return (NULL);
	}
	list_size = ft_lstsize(file_list);
	map_settings = init_map_settings(list_size);
	if (!map_settings)
	{
		free_list(&file_list);
		return (NULL);
	}
	evaluate_settings(file_list, &map_settings);
	if (map_settings->charmap == NULL)
	{
		free_evaluation(&map_settings);
		printf("Error: Something is wrong with the values in the .cub file\n");
		return (NULL);
	}
	return (map_settings);
}

t_list	*read_file(int fd)
{
	t_list	*file_list;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	file_list = ft_lstnew(line);
	if (!file_list)
	{
		printf("Error: Could not allocate memory for file_list\n");
		return (NULL);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			ft_lstadd_back(&file_list, line);
	}
	return (file_list);
}

void	load_charmap(t_settings **map_settings, \
	t_list *file_list, t_list **temp, int j)
{
	if (!((*map_settings)->charmap))
	{
		free_evaluation(map_settings);
		free_list(temp);
		exit(0);
	}
	while (file_list)
	{
		(*map_settings)->charmap[j] = ft_strdup(file_list->content);
		file_list = file_list->next;
		j++;
	}
	(*map_settings)->charmap[j] = NULL;
	free_list(temp);
}

void	evaluate_settings(t_list *file_list, t_settings **map_settings)
{
	int		i;
	int		j;
	t_list	*temp;

	temp = file_list;
	i = 0;
	j = 0;
	while (file_list && i < ELINFOLIMIT)
	{
		if (treat_caught_info((*map_settings)->elmap, &file_list, &i) == 1)
		{
			free_evaluation(map_settings);
			free_list(&temp);
			exit(0);
		}
		i++;
	}
	(*map_settings)->charmap = malloc(sizeof(char *) \
		* (ft_lstsize(temp) - ELINFOLIMIT + 1));
	load_charmap(map_settings, file_list, &temp, j);
}
