# include "../includes/cub3D.h"

static void action_nothing(t_object **this, t_game *game)
{
    (void)this;
    (void)game;
}

static t_imgbuffer    get_image_wall(t_object *this, int dir)
{
    t_imgbuffer img;
    t_wall *wall;

    wall = (t_wall *)this;
    if (dir == NORTH && wall->textures->n.img)
        img = wall->textures->n;
    if (dir == SOUTH && wall->textures->s.img)
        img = wall->textures->s;
    if (dir == EAST && wall->textures->e.img)
        img = wall->textures->e;
    if (dir == WEST && wall->textures->w.img)
        img = wall->textures->w;
    return (img);
}

t_object *new_wall(t_game *game)
{
    t_wall *wall;

    wall = ft_calloc(sizeof(t_wall), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    wall->action = action_nothing;
    wall->textures = &game->texture_wall;
    return ((t_object *)wall);
}
