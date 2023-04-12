# include "../includes/cub3D.h"

char	*elmapGet(t_elinfo *elmap ,char *elmapKey)
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

static void free_and_exit(t_elinfo *elmap, char **charmap, t_settings *settings)
{
    free(settings->Ntexpath);
	free(settings->Stexpath);
	free(settings->Wtexpath);
	free(settings->Etexpath);
	free(settings->Floorstr);
	free(settings->Ceilstr);
    free(settings);
    elmapFree(&elmap);
    charmapFree(charmap);
    printf("Invalid map info\n");
    exit(0);
}

// Improve this function so that it cleans all the empty lines from up and down
char **clean_map(char **map)
{
    char **new_map;
    int i;

    i = 0;
    while (map[i] != NULL)
        i++;
    new_map = malloc(sizeof(char *) * (i + 1));
    i = 0;
    while (map[i] != NULL)
    {
        new_map[i] = ft_strdup(map[i]);
        i++;
    }
    new_map[i] = NULL;
    charmapFree(map);
    return (new_map);
}

t_settings *settingsSet(t_elinfo *elmap, char **charmap)
{
    t_settings *settings;

    settings = malloc(sizeof(t_settings));
    settings->Ntexpath = elmapGet(elmap, "NO");
    settings->Stexpath = elmapGet(elmap, "SO");
    settings->Wtexpath = elmapGet(elmap, "WE");
    settings->Etexpath = elmapGet(elmap, "EA");
    settings->Floorstr = elmapGet(elmap, "F");
    settings->Ceilstr = elmapGet(elmap, "C");
    settings->charmap = clean_map(charmap);
	if ((settings->Ntexpath && settings->Stexpath
			&& settings->Wtexpath && settings->Etexpath
			&& settings->Floorstr && settings->Ceilstr
			&& settings->charmap) == 0) // if any of the settings are left blank
		free_and_exit(elmap, charmap, settings);
	return (settings);
}



int check_valid_filename(const char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] != '.')
		i--;
	str = str + i;
	return (!ft_strncmp(str, ".cub", 5));
}

int	fileXtract(char *cubflpath)
{
	int	fd;
	t_elinfo	*elmap;
	char		**charmap;
	t_settings	*settings;

	printf("Extracting content from %s\n", cubflpath);
	if (check_valid_filename(cubflpath) == 0)
	{
		printf("Invalid map file_name\n");
		exit(0);
	}
	fd = open(cubflpath, O_RDONLY);
	if (fd <= 0)
		exit(0); //TODO: fancy exit
	elmap = elmapXtract(fd);
	if (elmap == NULL)
	{
		printf("Invalid file data, exited extract\n");
		exit(0);
	}
	//TODO: there might be many \n between these two or none at all
    charmap = charmapXtract(fd); // review this, valgrind giving errors
	close(fd);
    settings = settingsSet(elmap, charmap);
	elmapFree(&elmap);

    printf("SETTINGS:\n");
    printf("Ntexpath: %s\n", settings->Ntexpath);
    printf("Stexpath: %s\n", settings->Stexpath);
    printf("Wtexpath: %s\n", settings->Wtexpath);
    printf("Etexpath: %s\n", settings->Etexpath);
    printf("Floorstr: %s\n", settings->Floorstr);
    printf("Ceilstr: %s\n", settings->Ceilstr);
    int k = 0;
    while (settings->charmap[k] != NULL)
    {
        printf("charmap[%d]: %s\n", k, settings->charmap[k]);
        k++;
    }

    /*for debug malloc , this is to erase
    */ 
    free(settings->Ntexpath);
    free(settings->Stexpath);
    free(settings->Wtexpath);
    free(settings->Etexpath);
    free(settings->Floorstr);
    free(settings->Ceilstr);
    charmapFree(settings->charmap);
    free(settings);
    
	//return (prep_game(&settings));
	return (0);
}
