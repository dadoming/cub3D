# include "../includes/cub3D.h"

static int			get_image_wall(t_object *this, int dir)
{
    return (rgbtocolor(255,0,0));
}

t_object *new_wall()
{
    t_object *wall;

    wall = ft_calloc(sizeof(t_object), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    return (wall);
}
