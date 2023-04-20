# include "../../includes/cub3D.h"

void free_evaluation(t_settings **map_settings)
{
    printf("Cleaning Settings.\n");
    
    elmapFree((*map_settings)->elmap);
    if ((*map_settings)->charmap)
        charmapFree((*map_settings)->charmap);
    if ((*map_settings)->Ntexpath)
        free((*map_settings)->Ntexpath);
    if ((*map_settings)->Stexpath)
        free((*map_settings)->Stexpath);
    if ((*map_settings)->Wtexpath)
        free((*map_settings)->Wtexpath);
    if ((*map_settings)->Etexpath)
        free((*map_settings)->Etexpath);
    if ((*map_settings)->Floorstr)
        free((*map_settings)->Floorstr);
    if ((*map_settings)->Ceilstr)
        free((*map_settings)->Ceilstr);
    free(*map_settings);
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

int	charmapFree(char **charmap)
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

void elmapFree(t_elinfo *elmap)
{
    int i;

    i = 0;
    while (i < ELINFOLIMIT)
    {
        if (elmap[i].key != NULL)
            free(elmap[i].key);
        if (elmap[i].val != NULL)
            free(elmap[i].val);
        i++;
    }
}