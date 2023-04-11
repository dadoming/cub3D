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

#define ARTLIMIT 100 //TODO: remove artificial limit

# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307

typedef struct s_img
{
	void	*ptr;
	int		width;
	int		height;
} t_img;

typedef struct s_game
{
    void	*mlx;
    void	*win;

	char	**charmap;
} t_game;

typedef struct s_settings
{
	char	*Ntexpath;
	char	*Stexpath;
	char	*Wtexpath;
	char	*Etexpath;

	char	*Floorstr;
	char	*Ceilstr;

	char	**charmap;
} t_settings;

typedef struct s_elinfo
{
	char	*key;
	char	*val;
} t_elinfo;


int check_input(int argc, char **argv);
int	fileXtract(char *cubflpath);
t_elinfo	*elmapXtract(int openfd);
int	elmapFree(t_elinfo *elmap);
char	*elmapGet(t_elinfo *elmap ,char *elmapKey);
char	**charmapXtract(int openfd);
int	charmapFree(char **charmap);

int	prep_game();
int run_game(t_game game);

# endif