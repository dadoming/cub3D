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
	printf("Activated: %d\n", (*this)->type);
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

void update_anim(t_animation *anim, microSeconds tmstmpnow)
{
    microSeconds timedifference;
	
    if (anim->trigger == 0)
        return;
	else if (anim->trigger == 1 && anim->frameCount == 1)
	{
        clock_gettime(CLOCK_MONOTONIC, &anim->startTime);
        // printf("AnimationFrame_%d: %ld\n", anim->frameCount, timestamp(anim->startTime));
        anim->frameCount++;
        return;
    }
    // timedifference = timediff(anim->startTime);
	timedifference = tmstmpnow - timestamp(anim->startTime);

	if (timedifference > anim->frameTime * (anim->frameCount - 1)) // animation time has passed
    {
		anim->frameCount++;
		anim->current_frame = anim->current_frame->next;
		if (anim->current_frame == NULL)
		{
			anim->trigger = 0; // Stops animation and resets
			anim->current_frame = anim->frames;
			anim->frameCount = 1;
		}
		// printf("AnimationFrame_%d: %ld\n", gun->frameCount, td);
		return;
	}
}