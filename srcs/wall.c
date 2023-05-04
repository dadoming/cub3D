# include "../includes/cub3D.h"

static int			get_image_wall(t_object *this, int dir)
{
    if (dir == NORTH)
        return (rgbtocolor(240,181,61));
    if (dir == SOUTH)
        return (rgbtocolor(148,71,21));
    if (dir == EAST)
        return (rgbtocolor(242,242,27));
    if (dir == WEST)
        return (rgbtocolor(238,108,88));
    return (rgbtocolor(255,255,255));
}

t_object *new_wall()
{
    t_object *wall;

    wall = ft_calloc(sizeof(t_object), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    return (wall);
}
