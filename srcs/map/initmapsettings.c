# include "../../includes/cub3D.h"

static void     init_map_settings_2(t_settings **map_settings);

t_settings *init_map_settings(int list_size)
{
    t_settings *map_settings;

    map_settings = malloc(sizeof(t_settings));
    if (!map_settings)
        return (NULL);
    init_map_settings_2(&map_settings);
    if (list_size < ELINFOLIMIT)
    {
        free(map_settings);
        printf("Error: Invalid map content\n");
        return (NULL);
    }
    return (map_settings);
}

static void init_map_settings_2(t_settings **map_settings)
{
    int i;

    i = 0;
    (*map_settings)->Ceilstr = NULL;
    (*map_settings)->Floorstr = NULL;
    (*map_settings)->Ntexpath = NULL;
    (*map_settings)->Stexpath = NULL;
    (*map_settings)->Wtexpath = NULL;
    (*map_settings)->Etexpath = NULL;
    (*map_settings)->charmap = NULL;
    while (i < ELINFOLIMIT)
    {
        (*map_settings)->elmap[i].key = NULL;
        (*map_settings)->elmap[i].val = NULL;
        i++;
    }
}

