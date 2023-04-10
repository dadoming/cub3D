# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"

int check_input(int argc, char **argv);
void run_game(char *map_path);

typedef struct s_game
{
    void *mlx;
    void *win;

} t_game;

# endif