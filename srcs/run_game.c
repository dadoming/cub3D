# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int x_close_window(t_game *game)
{
    close_game(game);
    return (0);
}

int key_event(int key, t_game *game)
{
    //printf("key> %d\n", key);
    if (key == ESC)
        close_game(game);
    return (0);
}

int run_game(t_game game, t_settings *setts)
{
    mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);
    mlx_hook(game.win, 2, 1L<<0, key_event, &game);
    mlx_loop(game.mlx);
	
	return (1);
}