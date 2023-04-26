#include "../../includes/cub3D.h"

static void     load_elinfo(t_elinfo *elinfo, char *file_line, int i, int option);
static int      load_info_from_line(t_elinfo *elinfo, char *file_line, int *i);

int treat_caught_info(t_elinfo *elinfo, t_list **file_list, int *i)
{
    int j;

    while ((*file_list) && *i < ELINFOLIMIT)
    {
        j = 0;
        while (ft_isspace((*file_list)->content[j]))
            j++;
        if ((*file_list)->content[j] == '\0' || (*file_list)->content[j] == '\n')
        {
            (*file_list) = (*file_list)->next;
            continue;
        }
        if (load_info_from_line(elinfo, &((*file_list)->content[j]), i) == 1)
            return (1);
        (*file_list) = (*file_list)->next;
        (*i)++;
    }
    return (0);
}

static int load_info_from_line(t_elinfo *elinfo, char *file_line, int *i)
{
    if (ft_strncmp("NO ", file_line, 3) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 1);
    else if (ft_strncmp("SO ", file_line, 3) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 1);
    else if (ft_strncmp("EA ", file_line, 3) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 1);
    else if (ft_strncmp("WE ", file_line, 3) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 1);
    else if (ft_strncmp("F ", file_line, 2) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 0);
    else if (ft_strncmp("C ", file_line, 2) == 0 && elinfo[*i].key == NULL)
        load_elinfo(elinfo, file_line, *i, 0);
    else
        return (1);
    return (0);
}

void load_elinfo(t_elinfo *elinfo, char *file_line, int i, int option)
{
    int spaces;
    int j;

    j = 0;
    spaces = 0;
    if (file_line[2 + option] == '\n' || file_line[2 + option] == '\0')
        return ;
    elinfo[i].key = ft_substr(file_line, 0, 1 + option + spaces);
    while (ft_isspace(file_line[2 + option + spaces]))
        spaces++;
    if (file_line[spaces + 2 + option] == '\n' || file_line[spaces + 2 + option] == '\0')
        return ;
    elinfo[i].val = ft_substr(file_line, 2 + option + spaces, ft_strlen(file_line) - 2 - option - spaces);
    while (elinfo[i].val[j])
    {
        if (i < 4 && ft_isspace(elinfo[i].val[j]))
            elinfo[i].val[j] = '\0';
        else if (i >= 4 && elinfo[i].val[j] == '\n')
            elinfo[i].val[j] = '\0';
        j++;
    }
}
