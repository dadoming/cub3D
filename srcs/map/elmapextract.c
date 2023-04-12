/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elmapextract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:35:26 by dadoming          #+#    #+#             */
/*   Updated: 2023/04/12 20:05:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_list  *read_file(int fd);
static t_settings *init_map_settings(int list_size);
void load_map(t_list *file_list, t_settings **map_settings);
int treat_caught_info(t_elinfo **map_settings, t_list **file_list, int *i);
void free_list(t_list **list);

t_settings	*elmapXtract(int openfd)
{
    t_list      *file_list;
    t_settings  *map_settings;
    int list_size;
    
    file_list = read_file(openfd);
    if (file_list == NULL)
    {
        printf("Error: File is empty\n");
        return (NULL);
    }
    list_size = ft_lstsize(file_list);
    map_settings = init_map_settings(list_size);
    if (!map_settings)
        return (NULL);
    load_map(file_list, &map_settings);
    if (map_settings->charmap == NULL)
    {
        //free_strucy
        return (NULL);
    }
    return(map_settings);
}

void load_map(t_list *file_list, t_settings **map_settings)
{
    int i;
    int j;
    t_list *temp;

    temp = file_list;
    i = 0;
    j = 0;
    while (file_list)
    {
        if (i < ELINFOLIMIT)
        {
            if (treat_caught_info(&((*map_settings)->elmap), &file_list, &i) == 1)
            {
                file_list = temp;
                //free_struct
                exit(0);
            }
        }
        else 
            break;
        i++;
    }
    printf("Map size: %d\n", ft_lstsize(file_list) + 1);
    (*map_settings)->charmap = malloc(sizeof(char *) * (ft_lstsize(temp) - i + 1));
    if (!(*map_settings)->charmap)
        exit(0); // and free
    while (file_list)
    {
        (*map_settings)->charmap[j] = ft_strdup(file_list->content);
        file_list = file_list->next;
        j++;
    }
    (*map_settings)->charmap[j] = 0;
    free_list(&temp);
}

void free_list(t_list **list)
{
    t_list *tmp;

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

void load_elinfo(t_elinfo **map_settings, char *file_line, int i, int option)
{
    int spaces;

    spaces = 0;
    if (file_line[2 + option] == '\n' || file_line[2 + option] == '\0')
        return ; // return NULL key
    (*map_settings)[i].key = ft_substr(file_line, 0, 1 + option + spaces);
    while (ft_isspace(file_line[2 + option + spaces]))
        spaces++;
    if (file_line[spaces + 2 + option] == '\n' || file_line[spaces + 2 + option] == '\0')
        return ; // return NULL val
    (*map_settings)[i].val = ft_substr(file_line, 2 + option + spaces, ft_strlen(file_line) - 2 - option - spaces);
}

int treat_caught_info(t_elinfo **map_settings, t_list **file_list, int *i)
{
    int j;

    while ((*file_list) && *i < ELINFOLIMIT)
    {
        j = 0;
        while (ft_isspace((*file_list)->content[j]))
            j++;
        if ((*file_list)->content[j] == '\0' || (*file_list)->content[j] == '\n')
        {
            (*file_list) = (*file_list)->next;
            continue;
        }
        if (ft_strncmp("NO ", &((*file_list)->content[j]), 3) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 1);
        else if (ft_strncmp("SO ", &((*file_list)->content[j]), 3) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 1);
        else if (ft_strncmp("EA ", &((*file_list)->content[j]), 3) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 1);
        else if (ft_strncmp("WE ", &((*file_list)->content[j]), 3) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 1);
        else if (ft_strncmp("F ", &((*file_list)->content[j]), 2) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 0);
        else if (ft_strncmp("C ", &((*file_list)->content[j]), 2) == 0 && (*map_settings)[*i].key == NULL)
            load_elinfo(map_settings, &((*file_list)->content[j]), *i, 0);
        else
            return (1);
        (*file_list) = (*file_list)->next;
        (*i)++;
    }

    return (0);
}

t_list  *read_file(int fd)
{
    t_list *file_list;
    char *line;

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

static t_settings *init_map_settings(int list_size)
{
    t_settings *map_settings;
    int i;

    i = 0;
    map_settings = malloc(sizeof(t_settings));
    if (!map_settings)
        return (NULL);
    map_settings->elmap = malloc(ELINFOLIMIT * sizeof(t_elinfo));
    if (!(map_settings->elmap))
        return (NULL);
    while (i < ELINFOLIMIT)
    {
        map_settings->elmap[i].key = NULL;
        map_settings->elmap[i].val = NULL;
        i++;
    }
    if (list_size < ELINFOLIMIT)
    {
        printf("Error: Map is too small\n");
        return (NULL);
    }
    return (map_settings);
}
