# include "../includes/cub3D.h"

static t_game* game(void)
{
    static t_game game;

    return (&game);
}

static void*    get_image_wall(t_object *this, int dir)
{
    if (dir == NORTH && game()->texture.n.img != NULL)
        return (game()->texture.n.img);
    if (dir == SOUTH && game()->texture.s.img != NULL)
        return (game()->texture.s.img);
    if (dir == EAST && game()->texture.e.img != NULL)
        return (game()->texture.e.img);
    if (dir == WEST && game()->texture.w.img != NULL)
        return (game()->texture.w.img);
    return ((void *)rgbtocolor(255,0,0));
}

t_object *new_wall()
{
    t_object *wall;

    wall = ft_calloc(sizeof(t_object), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    return (wall);
}
