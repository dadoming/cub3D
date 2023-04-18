# include "../../includes/cub3D.h"

char **rgb_split(char *value)
{
    char **rgb;
    int i;

    i = 0;
    rgb = ft_split(value, ',');
    if (rgb == NULL)
        return (NULL);
    if (ft_mtrxlen((void**)rgb) != 3)
    {
        printf("Error\nInvalid RGB input\n");
        while (rgb[i])
            free(rgb[i++]);
        free(rgb);
        return (NULL);
    }
    return (rgb);
}

int check_only_numbers(char *str, char **rgb, int i)
{
    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            i = 0;
            while (rgb[i])
                free(rgb[i++]);
            free(rgb);
            free(str);
            return (-1);
        }
        i++;
    }
    return (0);
}

static char *trim_spaces(char **rgb, int i)
{
    char *str;

    str = ft_strtrim(rgb[i], " ");
    if (str == NULL)
    {
        i = 0;
        while (rgb[i])
            free(rgb[i++]);
        free(rgb);
        return (NULL);
    }
    return (str);
}

static int atoi_this(char *str, char **rgb, int i, int *rgbi)
{
    rgbi[i] = ft_atoi(str);
    free(str);
    if (rgbi[i] < 0 || rgbi[i] > 255)
    {
        i = 0;
        while (rgb[i])
            free(rgb[i++]);
        free(rgb);
        return (-1);
    }
    return (0);
}

int load_rgb(char *value)
{
    char **rgb;
    char *str;
    int rgbi[3];
    int i;

    rgb = rgb_split(value);
    if (rgb == NULL)
        return (-1);
    i = 0;
    while (rgb[i])
    {
        str = trim_spaces(rgb, i);
        if (str == NULL)
            return (-1);
        if (check_only_numbers(str, rgb, i) == -1)
            return (-1);
        rgbi[i] = atoi_this(str, rgb, i, rgbi);
        if (rgbi[i] == -1)
            return (-1);
        i++;
    }
    i = 0;
    while (rgb[i])
        free(rgb[i++]);
    free(rgb);
    return (rgbtocolor(rgbi[0], rgbi[1], rgbi[2]));
}
