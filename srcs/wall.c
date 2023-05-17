# include "../includes/cub3D.h"

static t_imgbuffer    get_image_wall(t_object *this, int dir)
{
    t_imgbuffer img;

    if (dir == NORTH && this->textures->n.img)
        img = this->textures->n;
    if (dir == SOUTH && this->textures->s.img)
        img = this->textures->s;
    if (dir == EAST && this->textures->e.img)
        img = this->textures->e;
    if (dir == WEST && this->textures->w.img)
        img = this->textures->w;
    return (img);
}

t_object *new_wall(t_game *game)
{
    t_object *wall;

    wall = ft_calloc(sizeof(t_object), 1);
    wall->type = WALL;
    wall->get_image = get_image_wall;
    wall->action = action_nothing;
    wall->textures = &game->texture_wall;
    return (wall);
}
