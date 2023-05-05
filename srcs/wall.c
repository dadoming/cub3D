# include "../includes/cub3D.h"

static t_imgbuffer    get_image_wall(t_object *this, int dir)
{
    t_imgbuffer img;

    if (dir == NORTH && this->texture->n.img)
        img = this->texture->n;
    if (dir == SOUTH && this->texture->s.img)
        img = this->texture->s;
    if (dir == EAST && this->texture->e.img)
        img = this->texture->e;
    if (dir == WEST && this->texture->w.img)
        img = this->texture->w;
    return (img);
}

t_object *new_wall(t_game *game)
{
    t_object *wall;

    wall = ft_calloc(sizeof(t_object), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    wall->texture = &game->texture_wall;
    return (wall);
}
