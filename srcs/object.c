# include "../includes/cub3D.h"

t_imgbuffer	image_nothing(t_object *this, int dir)
{
	t_imgbuffer img;

	img = (t_imgbuffer){0};

	(void)this;
	(void)dir;
	return (img);
}

void    action_nothing(t_object **this, t_game *game)
{
    (void)this;
    (void)game;
    return;
}

t_object	*new_empty(t_game *game)
{
	t_object *empty;

	empty = ft_calloc(sizeof(t_object), 1);
	empty->type = 0;
	empty->get_image = image_nothing;
	empty->action = action_nothing;
	empty->textures = NULL;

	(void)game;
	return (empty);
}