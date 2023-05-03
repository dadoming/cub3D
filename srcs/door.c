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

static int			get_image_door(t_object *this, int dir)
{
	(void) dir; // this is gonna be the side of the door to print
	if (((t_door *) this)->state == 1)
		return (rgbtocolor(0, 255, 0));
	return (rgbtocolor(0, 0, 255));
}

t_object *new_door(int x, int y)
{
	t_door *door;

	door = ft_calloc(sizeof(t_door), 1);
	door->x = x;
	door->y = y;
	door->state = 0;
	door->type = DOOR;
	door->action = action_door;
	door->get_image = get_image_door;
	return ((t_object *) door);
}
