# include "../../includes/cub3D.h"

int	charmapFree(char **charmap)
{
	size_t	i;

	if (!charmap)
		return (0);
	i = 0;
	while (charmap[i] != NULL)
	{
		free(charmap[i]);
		i++;
	}
	free(charmap);
	return (1);
}
