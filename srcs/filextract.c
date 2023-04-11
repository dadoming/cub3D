# include "../includes/cub3D.h"

t_settings	settingsSet(t_elinfo *elmap, char **charmap)
{
	t_settings	settings;
	int			check;

	ft_memset(&settings, 0, sizeof(t_settings)); // like a calloc on stack
	settings.Ntexpath = ft_strdup(elmapGet(elmap, "NO"));
	settings.Stexpath = ft_strdup(elmapGet(elmap, "SO"));
	settings.Wtexpath = ft_strdup(elmapGet(elmap, "WE"));
	settings.Etexpath = ft_strdup(elmapGet(elmap, "EA"));

	settings.Floorstr = ft_strdup(elmapGet(elmap, "F"));
	settings.Ceilstr = ft_strdup(elmapGet(elmap, "C"));

	settings.charmap = charmap;

	check = settings.Ntexpath && settings.Stexpath
			&& settings.Wtexpath && settings.Etexpath
			&& settings.Floorstr && settings.Ceilstr
			&& settings.charmap;
	
	if (check == 0) // if any of the settings are left blank
	{
		free(settings.Ntexpath);
		free(settings.Stexpath);
		free(settings.Wtexpath);
		free(settings.Etexpath);
		free(settings.Floorstr);
		free(settings.Ceilstr);
		elmapFree(elmap);
		charmapFree(charmap);
		exit(0);
	}
	return (settings);
}

int	fileXtract(char *cubflpath)
{
	int	fd;
	t_elinfo	*elmap;
	char		**charmap;
	t_settings	settings;

	printf("Extracting content from %s\n", cubflpath);
	fd = open(cubflpath, O_RDONLY);
	if (fd <= 0)
		exit(0); //TODO: fancy exit
	elmap = elmapXtract(fd);
	//TODO: there might be many \n between these two
	charmap = charmapXtract(fd);

	close(fd);

	settings = settingsSet(elmap, charmap);

	elmapFree(elmap);

	return (prep_game(&settings));
}
