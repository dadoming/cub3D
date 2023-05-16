# include "../includes/cub3D.h"

void	    load_door_idle(t_game *game)
{
    game->door_idle.frameNum = 8;
    game->door_idle.frames = load_n_images(game, "CapySitIdle/capybaraSittingIdle", game->door_idle.frameNum);
    game->door_idle.current_frame = game->door_idle.frames;
    game->door_idle.trigger = 0;
    game->door_idle.frameCount = 1;

    game->door_idle.frameTime = 200000;
    game->door_idle.startTime.tv_sec = 0;
    game->door_idle.startTime.tv_nsec = 0;
}

static void 		action_door(t_object **this, t_game *game)
{
	t_door *door;
	float dist;

	door = (t_door *)(*this);
// 	dist = sqrt(pow(game->player.pos.x - door->x, 2) + pow(game->player.pos.y - door->y, 2));
// 	printf("dist: %f\n", dist); // it looks like it has different values for different positions
// 	if (dist <= 2)
// 		door->state = !door->state;
	door->animation->trigger = 1;
}

static t_imgbuffer	get_image_door(t_door *this, int dir)
{
    t_imgbuffer img;

	// img = (t_imgbuffer){0};
    // if (dir == 0)
        // img = *(this->texture_door_closed);
    // else if (dir == 1)
        // img = *(this->texture_door_opened);
    // return (img);

	if (this->animation->trigger == 0)
		return (*this->texture_door_closed);
	else
		return (this->animation->current_frame->img);
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
    door->texture_door_opened = &game->texture_transparent;

	door->animation = &game->door_idle;
	// door->texture = &door->animation->current_frame->img;
	// door->texture = &game->texture_door;

	return ((t_object *)door);
}
