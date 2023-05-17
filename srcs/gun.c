# include "../includes/cub3D.h"

void draw_weapon(t_game *game)
{
    int i;
    int j;
    int spot_x;
    int spot_y;
    int color;


    spot_x = WINDOWSIZE_X / 2 - game->player_shoot.current_frame->img.width / 2;
    spot_y = WINDOWSIZE_Y - game->player_shoot.current_frame->img.height;
    i = 0;
    while (i < game->player_shoot.current_frame->img.height)
    {
        j = 0;
        while (j < game->player_shoot.current_frame->img.width)
        {
            color = mypixelget(&game->player_shoot.current_frame->img, j, i);
            if ((color & 0x00FFFFFF) != 0)
                mypixelput(&game->imgbuffer, spot_x + j, spot_y + i, color);
            j++;
        }
        i++;
    }
}

    

void update_gun(t_animation *gun)
{
    microSeconds td;
    if (gun->trigger == 0)
        return;
	else if (gun->trigger == 1 && gun->frameCount == 1)
	{
        clock_gettime(CLOCK_MONOTONIC, &gun->startTime);
        // printf("AnimationFrame_%d: %ld\n", gun->frameCount, timestamp(gun->startTime));
        gun->frameCount++;
        return;
    }
    td = timediff(gun->startTime);
    if (td > gun->frameTime * (gun->frameCount - 1)) // animation time has passed
    {
		gun->frameCount++;
		gun->current_frame = gun->current_frame->next;
		if (gun->current_frame == NULL)
		{
			gun->trigger = 0; // Stops animation and resets
			gun->current_frame = gun->frames;
			gun->frameCount = 1;
		}
		// printf("AnimationFrame_%d: %ld\n", gun->frameCount, td);
		return;
	}
    // printf("AnimationFrame_%d: %ld\n", gun->frameCount, td);

	// printf("timediff: %d\n", timediff(gun->startTime));

	// static t_anim_list *current_frame = NULL;
	// int time_now;
	// int time_old;

	// if (current_frame == NULL)
    //     current_frame = game->player_shoot.frames;
    // if (game->player_shoot.trigger == 1)
    // {
        // gettimeofday(&game->now_time, NULL);
        // time_now = game->now_time.tv_sec * 1000 + game->now_time.tv_usec / 1000;
        // time_old = game->old_time.tv_sec * 1000 + game->old_time.tv_usec / 1000;
        // if (time_now - time_old > 60)
        // {
            // game->old_time = game->now_time;
            // printf("time: %d\n", time_now - time_old);
            // if (game->player_shoot.frameCount > 0)
            // {
            //     game->player_shoot.current_frame = current_frame;
            //     current_frame = current_frame->next;
            //     game->player_shoot.frameCount--;
            // }
            // if (game->player_shoot.frameCount == 0)
            // {
            //     game->player_shoot.trigger = 0;
            //     game->player_shoot.frameCount = game->player_shoot.frameNum;
            //     current_frame = NULL;
            //     game->player_shoot.current_frame = game->player_shoot.frames;
            // }
        // }
        
    // }
}
