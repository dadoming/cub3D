# include "../includes/cub3D.h"



int	theloop(t_game *game)
{
    game->player.pos.y = game->player.inv_pos.x;
    game->player.pos.x = game->player.inv_pos.y;
	myclearimg(game);
	//draw_map(game);
	//draw_player(game);
	draw_ray(game);
	//if (game->minimap_toggle == 0)
	//{
	//    draw_minimap(game, game->player.pos); // sometimes memleaks
    //	//draw_full_minimap(game);
	//}
    mlx_put_image_to_window(game->mlx, game->win, game->imgbuffer.img, 0, 0);
    return (0);
}

int run_game(t_game *game)
{
	mlx_loop_hook(game->mlx, theloop, game);
    mlx_loop(game->mlx);
	return (1);
}