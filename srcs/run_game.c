# include "../includes/cub3D.h"

int mypixelget(t_imgbuffer *imgbuffer, int x, int y)
{
    int color;
    int offset;

    offset = imgbufferoffset(imgbuffer, x, y);
    color = *(int *)(imgbuffer->addr + offset);
    return (color);
}

void draw_weapon(t_game *game)
{
    int i;
    int j;
    int spot_x;
    int spot_y;
    int color;


    spot_x = WINDOWSIZE_X / 2 - game->player_animation.current_frame->img.width / 2;
    spot_y = WINDOWSIZE_Y - game->player_animation.current_frame->img.height;
    i = 0;
    while (i < game->player_animation.current_frame->img.height)
    {
        j = 0;
        while (j < game->player_animation.current_frame->img.width)
        {
            color = mypixelget(&game->player_animation.current_frame->img, j, i);
            if ((color & 0x00FFFFFF) != 0)
                mypixelput(&game->imgbuffer, spot_x + j, spot_y + i, color);
            j++;
        }
        i++;
    }
}

    

void update_gun(t_game *game)
{
    static t_anim_list *current_frame = NULL;
    int time_now;
    int time_old;

    if (current_frame == NULL)
        current_frame = game->player_animation.frames;
    if (game->player_animation.trigger == 1)
    {
        gettimeofday(&game->now_time, NULL);
        time_now = game->now_time.tv_sec * 1000 + game->now_time.tv_usec / 1000;
        time_old = game->old_time.tv_sec * 1000 + game->old_time.tv_usec / 1000;
        if (time_now - time_old > 60)
        {
            game->old_time = game->now_time;
            printf("time: %d\n", time_now - time_old);
            if (game->player_animation.frameCount > 0)
            {
                game->player_animation.current_frame = current_frame;
                current_frame = current_frame->next;
                game->player_animation.frameCount--;
            }
            if (game->player_animation.frameCount == 0)
            {
                game->player_animation.trigger = 0;
                game->player_animation.frameCount = game->player_animation.frameNum;
                current_frame = NULL;
                game->player_animation.current_frame = game->player_animation.frames;
            }
        }
        
    }
}

void update(t_game *game)
{
    update_gun(game);
}

int	theloop(t_game *game)
{
    //static int refresh_rate = 0;
    //if (refresh_rate != 500)
    //{
    //    refresh_rate++;
    //    return (0);
    //}
    //refresh_rate = 0;
    
    
    
    update(game);
    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;
	myclearimg(game);
	draw_ray(game);
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
    draw_weapon(game);
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
    return (0);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}