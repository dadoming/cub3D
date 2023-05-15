# include "../includes/cub3D.h"

static t_imgbuffer  get_image_dynamite(t_dynamite *this, int dir)
{
    (void)dir;
    return (*this->texture);
}

t_object *new_dynamite(t_game *game)
{
    t_dynamite *dynamite;

    dynamite = ft_calloc(sizeof(t_dynamite), 1);
    dynamite->type = DYNAMITE;
    dynamite->get_image = get_image_dynamite;
    // dynamite->action = //TODO: activates the explosion...
    // Time based explosion cant be done because we dont iterate through all objects 
    dynamite->texture = &game->texture_dynamite;

    return ((t_object *)dynamite);
}