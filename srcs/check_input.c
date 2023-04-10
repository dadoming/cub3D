# include "../includes/cub3D.h"

#define ARTLIMIT 100 //TODO: remove artificial limit
/*
 * This function will not check the last '\0'
 * Remember: pos is not index!
*/
size_t	ft_strpos(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

int	elmapFree(t_elinfo *elmap)
{
	size_t	i;

	i = 0;
	while (i < ARTLIMIT + 1)
	{
		free(elmap[i].key);
		free(elmap[i].val);
		i++;
	}
	return (1);
}

/**
 * 2 mallocs!!
*/
t_elinfo	lineTransform(char *rawline)
{
	t_elinfo	element;
	size_t		space[2];

	space[0] = ft_strpos(rawline, ' ');
	if (space[0] == 0)
		element.key = NULL;
	else
		element.key = ft_substr(rawline, 0, space[0]);
	
	if (rawline[space[0] + 1] == '\n'
		|| rawline[space[0] + 1] == '\0'
			|| space[0] == 0)
		element.val = NULL;
	else
		element.val = ft_substr(rawline, space[0] + 1, 0U-1);
	
	return (element);
}

t_elinfo	*fileXtract(char *cubflpath)
{
	int	fd;
	char	*raw;
	t_elinfo	*elmap;
	size_t	i;

	printf("Extracting content from %s\n", cubflpath);
	fd = open(cubflpath, O_RDONLY);
	if (fd <= 0)
		return (NULL);

	elmap = ft_calloc(ARTLIMIT, sizeof(t_elinfo)); //TODO: remove artificial limit
	i = 0;

	raw = get_next_line(fd);

	while (raw && i < 6)
	{
		printf("%s", raw);
		if (ft_strcmp(raw, "\n") == 0)
		{
			free(raw);
			raw = get_next_line(fd);
			continue;
		}


		elmap[i] = lineTransform(raw);
		printf("%s__%s\n", elmap[i].key, elmap[i].val);

		free(raw);
		if (elmap[i].key == NULL || elmap[i].val == NULL)
		{
			elmapFree(elmap);
			close(fd);
			return (NULL);
		}
		
		i++;
		
		raw = get_next_line(fd);
	}
	//TODO: extract the map section
	close(fd);
	//TODO: ? run_game(settings);
	return (elmap);
}

int check_input(int argc, char **argv)
{
	t_settings	settings;

    if (argc == 1)
    {
		fileXtract("maps/test.cub");
    }
	else if (argc == 2)
	{
		fileXtract(argv[1]);
	}
	else
	{
		printf("Wrong number of args");
		exit(0);
	}
	//TODO: ? run_game(settings);
}