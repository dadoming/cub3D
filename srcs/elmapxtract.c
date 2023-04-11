# include "../includes/cub3D.h"

int	elmapFree(t_elinfo *elmap)
{
	size_t	i;

	i = 0;
	while (i < ARTLIMIT)
	{
		free(elmap[i].key);
		free(elmap[i].val);
		i++;
	}
	free(elmap);
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
	//TODO: there can be more than 1 space!!!
	if (rawline[space[0] + 1] == '\n'
		|| rawline[space[0] + 1] == '\0'
			|| space[0] == 0)
		element.val = NULL;
	else
	{
		element.val = ft_substr(rawline, space[0] + ft_notstrpos(rawline + space[0], " "), 0U-1);
		element.val[ft_strlen(element.val) - 1] = '\0'; // \n -> \0
	}
	
	return (element);
}

t_elinfo	*elmapXtract(int openfd)
{
	t_elinfo	*elmap;
	char		*raw;
	size_t		i;

	elmap = ft_calloc(ARTLIMIT, sizeof(t_elinfo)); //TODO: remove artificial limit

	raw = get_next_line(openfd);

	i = 0;
	while (raw && i < 6)
	{
		printf("%s", raw);
		if (ft_strcmp(raw, "\n") == 0)
		{
			free(raw);
			raw = get_next_line(openfd);
			continue;
		}


		elmap[i] = lineTransform(raw);
		printf("%s__%s\n", elmap[i].key, elmap[i].val);

		free(raw);
		if (elmap[i].key == NULL || elmap[i].val == NULL)
		{
			elmapFree(elmap);
			close(openfd);
			return (NULL);
		}
		
		i++;
		
		raw = get_next_line(openfd);
	}
	free(raw);

	return (elmap);
}

char	*elmapGet(t_elinfo *elmap ,char *elmapKey)
{
	size_t	i;

	i = 0;
	while (i < ARTLIMIT)
	{
		if (ft_strcmp(elmapKey, elmap[i].key) == 0)
			return (elmap[i].val);
		i++;
	}
	return (NULL);
}