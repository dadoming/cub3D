/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filextract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:26:31 by dadoming          #+#    #+#             */
/*   Updated: 2023/04/14 14:38:45 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static char     *elmapGet(t_elinfo *elmap ,char *elmapKey);
t_settings      *settingsSet(t_settings *map_settings);
static int      check_valid_filename(const char *str);

int	fileXtract(char *cubflpath)
{
	int	fd;
	t_settings	*settings;

	printf("Extracting content from: %s\n", cubflpath);
	if (check_valid_filename(cubflpath) == 0)
	{
		printf("Invalid map filename!\nExiting program...\n");
		exit(0);
	}
	fd = open(cubflpath, O_RDONLY);
	if (fd <= 0)
	{
        printf("Could not open file!\nExiting program...\n");
        exit(0);
    }
    settings = read_settings(fd);
	if (settings == NULL)
	{
		printf("Exiting program...\n");
        close(fd);
		exit(0);
	}
    close(fd);
    settings = settingsSet(settings);
	return (prep_game(settings));
    //return (prepare_map(settings));
    
    /*for debug malloc , this is to erase
    */ 
    printf("SETTINGS:\n");
    printf("Ntexpath: %s", settings->Ntexpath);
    printf("Stexpath: %s", settings->Stexpath);
    printf("Wtexpath: %s", settings->Wtexpath);
    printf("Etexpath: %s", settings->Etexpath);
    printf("Floorstr: %s", settings->Floorstr);
    printf("Ceilstr: %s", settings->Ceilstr);
    int k = 0;
    if (settings->charmap != 0)
    {
        while (settings->charmap[k])
        {
            printf("charmap[%d]: %s", k, settings->charmap[k]);
            k++;
        }
    }
    free(settings->Ntexpath);
    free(settings->Stexpath);
    free(settings->Wtexpath);
    free(settings->Etexpath);
    free(settings->Floorstr);
    free(settings->Ceilstr);
    if (settings->charmap != NULL)
        charmapFree(settings->charmap);
    elmapFree(&settings->elmap);
    free(settings);
    
	return (0);
}

t_settings *settingsSet(t_settings *map_settings)
{
    map_settings->Ntexpath = elmapGet(map_settings->elmap, "NO");
    map_settings->Stexpath = elmapGet(map_settings->elmap, "SO");
    map_settings->Wtexpath = elmapGet(map_settings->elmap, "WE");
    map_settings->Etexpath = elmapGet(map_settings->elmap, "EA");
    map_settings->Floorstr = elmapGet(map_settings->elmap, "F");
    map_settings->Ceilstr = elmapGet(map_settings->elmap, "C");
    if ((map_settings->Ntexpath && map_settings->Stexpath \
			&& map_settings->Wtexpath && map_settings->Etexpath \
			&& map_settings->Floorstr && map_settings->Ceilstr \
			&& map_settings->charmap) == 0)
		free_on_invalid(map_settings);
	return (map_settings);
}

static char *elmapGet(t_elinfo *elmap ,char *elmapKey)
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


static int check_valid_filename(const char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && str[i] != '.')
		i--;
	str = str + i;
	return (!ft_strncmp(str, ".cub", 5));
}

void free_on_invalid(t_settings *settings)
{
    free(settings->Ntexpath);
	free(settings->Stexpath);
	free(settings->Wtexpath);
	free(settings->Etexpath);
	free(settings->Floorstr);
	free(settings->Ceilstr);
    charmapFree(settings->charmap);
    elmapFree(&settings->elmap);
    free(settings);
    printf("Error: Invalid map info\n");
    exit(0);
}
