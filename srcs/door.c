# include "../includes/cub3D.h"

static void 		action_door(t_object **this, t_game *game)
{
	t_door *door;
	float dist;

	door = (t_door *)(*this);
	dist = sqrt(pow(game->player.pos.x - door->x, 2) + pow(game->player.pos.y - door->y, 2));
	printf("dist: %f\n", dist);
	if (dist <= 2)
		door->state = !door->state;
	door->animation = game->capy_walk;
}

static t_imgbuffer	get_image_door(t_door *this, int dir)
{
	return (this->animation.current_frame->img);
	(void)dir;
}

t_object *new_door(int x, int y, t_game *game)
{
	t_door *door;

	door = ft_calloc(sizeof(t_door), 1);
	door->type = DOOR;
	door->get_image = get_image_door;
	door->action = action_door;
	door->x = x;
	door->y = y;
	door->state = 0;
    door->texture_door_closed = &game->texture_door;

	door->animation = game->capy_idle;

	return ((t_object *)door);
}
