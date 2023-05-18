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
    microseconds td;
    if (gun->trigger == 0)
        return;
	else if (gun->trigger == 1 && gun->frameCount == 1)
	{
        clock_gettime(CLOCK_MONOTONIC, &gun->startTime);
        gun->frameCount++;
        return;
    }
    td = timediff(gun->startTime);
    if (td > gun->frameTime * (gun->frameCount - 1))
    {
		gun->frameCount++;
		gun->current_frame = gun->current_frame->next;
		if (gun->current_frame == NULL)
		{
			gun->trigger = 0;
			gun->current_frame = gun->frames;
			gun->frameCount = 1;
		}
		return;
	}
}
