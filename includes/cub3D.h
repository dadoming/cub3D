# ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
// #include <libft.h>
#include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307

typedef struct s_game
{
    void *mlx;
    void *win;

} t_game;

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
} t_img;

typedef struct s_elinfo
{
	char	*key;
	char	*val;
} t_elinfo;


typedef struct s_settings
{
	t_img	Ntex;
	t_img	Stex;
	t_img	Wtex;
	t_img	Etex;
	// t_color	Floor;
	// t_color Ceil;
} t_settings;

int check_input(int argc, char **argv);
void run_game(char *map_path);

# endif