# include "../includes/cub3D.h"

static void 		action_door(t_object *this, t_game *game)
{
	t_door *door;
	float dist;

	door = (t_door *) this;
	dist = sqrt(pow(game->player.pos.x - door->x, 2) + pow(game->player.pos.y - door->y, 2));
	printf("dist: %f\n", dist); // it looks like it has different values for different positions
	if (dist <= 2)
		door->state = !door->state;
}

static t_imgbuffer	get_image_door(t_door *this, int dir)
{
    t_imgbuffer img;

	img = (t_imgbuffer){0};
    if (dir == 0)
        img = *(this->texture_door_closed);
    else if (dir == 1)
        img = *(this->texture_door_opened);
    return (img);
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
	door->type = DOOR;
    door->texture_door_closed = &game->texture_door;
    door->texture_door_opened = &game->texture_transparent;
    return ((t_object *)door);
}
