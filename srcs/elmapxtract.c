# include "cub3D.h"

void init_map_settings(t_elinfo **map_settings)
{
    int i;

    i = 0;
    *map_settings = ft_calloc(ELINFOLIMIT, sizeof(t_elinfo));
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
    while (ft_isspace(file_line[spaces]))
        spaces++;
    if (file_line[spaces + 2 + option] == '\0')
        return ;
    (*map_settings)[i].key = ft_substr(file_line, 0, 2 + option + spaces);
    while (ft_isspace(file_line[2 + option + spaces]))
        spaces++;
    if (file_line[spaces + 2 + option] == '\0')
        return ;
    (*map_settings)[i].val = ft_substr(file_line, 2 + option + spaces, ULONG_MAX);
}

int treat_caught_info(t_elinfo **map_settings, char *file_line, int i)
{
    int error;

    error = 0;
    if (ft_strncmp("NO ", file_line, 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 1);
    else if (ft_strncmp("SO ", file_line, 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 1);
    else if (ft_strncmp("EA ", file_line, 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 1);
    else if (ft_strncmp("WE ", file_line, 3) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 1);
    else if (ft_strncmp("F ", file_line, 2) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 0);
    else if (ft_strncmp("C ", file_line, 2) == 0 && (*map_settings)[i].key == NULL)
        load_elinfo(map_settings, file_line, i, 0);
    else
        error = 1;
    return (error);
}

void free_loaded(t_elinfo **map_settings)
{
    int i;

    i = 0;
    while (i < ELINFOLIMIT)
    {
        if (map_settings[i]->key != NULL)
            free((*map_settings)[i].key);
        if (map_settings[i]->val != NULL)
            free((*map_settings)[i].val);
        i++;
    }
}

t_elinfo	*elmapXtract(int openfd)
{
    t_elinfo    *map_settings;
    char        *file_line;
    int         i;

    init_map_settings(&map_settings);
    file_line = get_next_line(openfd);
    i = 0;
    while (file_line)
    {
        printf("file_line: %s\n", file_line);
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
                free_loaded(&map_settings);
                return (NULL);
            }
            free(file_line);
            file_line = get_next_line(openfd);
            i++;
        }
    }
    return (map_settings);
}