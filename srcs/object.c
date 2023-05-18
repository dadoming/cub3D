# include "../includes/cub3D.h"

void update_anim(t_animation *anim, microseconds tmstmpnow)
{
    microseconds timedifference;
	
    if (anim->trigger == 0)
        return;
	else if (anim->trigger == 1 && anim->frameCount == 1)
	{
        clock_gettime(CLOCK_MONOTONIC, &anim->startTime);
        anim->frameCount++;
        return;
    }
	timedifference = tmstmpnow - timestamp(anim->startTime);
	if (timedifference > anim->frameTime * (anim->frameCount - 1))
    {
		anim->frameCount++;
		anim->current_frame = anim->current_frame->next;
		if (anim->current_frame == NULL)
		{
			anim->trigger = 0;
			anim->current_frame = anim->frames;
			anim->frameCount = 1;
		}
	}
}