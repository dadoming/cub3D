# include "../includes/cub3D.h"

// Ezequiel
static char	**aux(int fd, char **map, size_t count)
{
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		map = aux(fd, map, count + 1);
	}
	else
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
			exit(0);
	}
	map[count] = line;
	return (map);
}

char	**charmapXtract(int openfd)
{
	return (aux(openfd, NULL, 0));
}

int	charmapFree(char **charmap)
{
	size_t	i;

	i = 0;
	while (charmap[i] != NULL)
	{
		free(charmap[i]);
		i++;
	}
	free(charmap);
	return (1);
}
