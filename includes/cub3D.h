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

#define ELINFOLIMIT 6 //TODO: remove artificial limit

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

typedef struct s_vec2i
{
	int	x;
	int	y;
}				t_vec2i;

typedef struct s_vec2f
{
	float	x;
	float	y;
}				t_vec2f;

int check_input(int argc, char **argv);
int	fileXtract(char *cubflpath);
t_elinfo	*elmapXtract(int openfd);
int	elmapFree(t_elinfo *elmap);
char	*elmapGet(t_elinfo *elmap ,char *elmapKey);
char	**charmapXtract(int openfd);
int	charmapFree(char **charmap);

int	prep_game();
int run_game(t_game game);

int	rgbtocolor(unsigned char r, unsigned char g, unsigned char b);
int	line(t_game *game, t_vec2i origin, t_vec2i dest, int color);





# endif