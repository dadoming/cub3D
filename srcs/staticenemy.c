# include "../includes/cub3D.h"

void	action_staticenemy(t_object **this, t_game *game)
{
	(void)this;
	(void)game;
	return;
}

t_imgbuffer	get_image_staticenemy(t_staticenemy *this, int dir)
{
	return (this->animation.current_frame->img);
}

t_object	*new_staticenemy(t_game *game)
{
	t_staticenemy *staticenemy;

	staticenemy = ft_calloc(sizeof(t_staticenemy), 1);
	staticenemy->type = STATICENEMY;
	staticenemy->get_image = get_image_staticenemy;
	staticenemy->action = action_staticenemy;
	staticenemy->animation = game->capy_munch;
}