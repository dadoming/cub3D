# include "../includes/cub3D.h"

void	update_anim(t_animation *anim, t_microseconds tmstmpnow)
{
	t_microseconds	timedifference;

	if (anim->trigger == 0)
		return ;
	else if (anim->trigger == 1 && anim->frame_count == 1)
	{
		clock_gettime(CLOCK_MONOTONIC, &anim->start_time);
		anim->frame_count++;
		return ;
	}
	timedifference = tmstmpnow - timestamp(anim->start_time);
	if (timedifference > anim->frame_time * (anim->frame_count - 1))
	{
		anim->frame_count++;
		anim->current_frame = anim->current_frame->next;
		if (anim->current_frame == NULL)
		{
			anim->trigger = 0;
			anim->current_frame = anim->frames;
			anim->frame_count = 1;
		}
	}
}

t_object	***load_individual_map_tile(char **map, t_game *game)
{
	int			i;
	int			j;
	t_object	***obj;

	obj = ft_calloc(sizeof(t_object **), (ft_mtrxlen((void **)map) + 1));
	if (!obj)
		return (NULL);
	i = -1;
	while (map[++i])
	{
		obj[i] = ft_calloc(sizeof(t_object *), ft_strlen(map[i]) + 1);
		if (!obj[i])
			return (NULL);
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == DOOR)
				obj[i][j] = new_door(j, i, game);
			else if (map[i][j] == WALL)
				obj[i][j] = new_wall(game);
			else if (map[i][j] == STATICENEMY)
				obj[i][j] = new_staticenemy(game);
		}
	}
	return (obj);
}

void free_objmap(char **map, t_object ***obj)
{
    int i = 0;
    int j = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == DOOR)
                free(obj[i][j]);
            else if (map[i][j] == WALL)
                free(obj[i][j]);
            j++;
        }
        free(obj[i]);
        i++;
    }
    free(obj);
}
