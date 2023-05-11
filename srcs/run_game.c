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

void update(t_game *game)
{
    static t_anim_list *current_frame = NULL;

    if (current_frame == NULL)
        current_frame = game->player_animation.frames;
    if (game->player_animation.trigger == 1)
    {
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



int	theloop(t_game *game)
{
    static int i = 0;
    if (i != 1500)
    {
        i++;
        return (0);
    }
    mlx_mouse_move(game->mlx, game->win, WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
    i = 0;
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