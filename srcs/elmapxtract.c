# include "cub3D.h"

void init_map_settings(t_elinfo **map_settings)
{
    int i;

    i = 0;
    *map_settings = malloc(ELINFOLIMIT * sizeof(t_elinfo));
    if (!(*map_settings))
        exit(0); // fancy exit
    while (i < ELINFOLIMIT)
    {
        (*map_settings)[i].key = NULL;
        (*map_settings)[i].val = NULL;
        i++;
    }
}

void load_elinfo(t_elinfo **map_settings, char *file_line, int i, int option)
{
    int spaces;

    spaces = 0;
    if (file_line[2 + option] == '\n' || file_line[2 + option] == '\0')
        return ; // return NULL key
    (*map_settings)[i].key = ft_substr(file_line, 0, 1 + option + spaces);
    while (ft_isspace(file_line[2 + option + spaces]))
        spaces++;
    if (file_line[spaces + 2 + option] == '\n' || file_line[spaces + 2 + option] == '\0')
        return ; // return NULL val
    (*map_settings)[i].val = ft_substr(file_line, 2 + option + spaces, ft_strlen(file_line) - 2 - option - spaces);
}

int treat_caught_info(t_elinfo **map_settings, char *file_line, int i)
{
    int error;
    int j;

    error = 0;
    j = 0;
    while (ft_isspace(file_line[j]))
        j++;
    if (ft_strncmp("NO ", &file_line[j], 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 1);
    else if (ft_strncmp("SO ", &file_line[j], 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 1);
    else if (ft_strncmp("EA ", &file_line[j], 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 1);
    else if (ft_strncmp("WE ", &file_line[j], 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 1);
    else if (ft_strncmp("F ", &file_line[j], 2) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 0);
    else if (ft_strncmp("C ", &file_line[j], 2) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, &file_line[j], i, 0);
    else
        error = 1;
    return (error);
}

void elmapFree(t_elinfo **map_settings)
{
    int i;

    i = 0;
    while (i < ELINFOLIMIT)
    {
        if ((*map_settings)[i].key != NULL)
            free((*map_settings)[i].key);
        if ((*map_settings)[i].val != NULL)
            free((*map_settings)[i].val);
        i++;
    }
    free(*map_settings);
}

t_elinfo	*elmapXtract(int openfd)
{
    t_elinfo    *map_settings;
    char        *file_line;
    int         i;

    init_map_settings(&map_settings);
    file_line = get_next_line(openfd);
    i = 0;
    while (file_line && i < ELINFOLIMIT)
    {
        if (ft_strcmp(file_line, "\n") == 0)
        {
            free(file_line);
            file_line = get_next_line(openfd);
            continue ;
        }
        else
        {
            if (treat_caught_info(&map_settings, file_line, i) == 1)
            {
                free(file_line);
                elmapFree(&map_settings);
                return (NULL);
            }
            free(file_line);
            file_line = get_next_line(openfd);
            i++;
        }
    }
    free(file_line);
    // ficou uma linha guardada no get_next_line?
    
    

    /* Print values map_settings
    int j = 0;
    while (j < ELINFOLIMIT)
    {
        printf("%s %s", map_settings[j].key, map_settings[j].val);
        j++;
    }
    */
    return (map_settings);
}