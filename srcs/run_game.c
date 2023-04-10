# include "../includes/cub3D.h"

void close_game(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int x_close_window(int keycode, t_game *game)
{
    printf("keycode: %d\n", keycode);
    close_game(game);
    return (0);
}

void run_game(char *map_path)
{
    (void) map_path;
    static t_game game;

    game.mlx = mlx_init();
    if (!game.mlx)
        return ;
    game.win = mlx_new_window(game.mlx, 800, 500, "cub3D");
    
    mlx_hook(game.win, 17, 1L<<2, x_close_window, &game);

    mlx_loop(game.mlx);
}