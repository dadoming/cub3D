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
# include <limits.h>

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

typedef struct s_elinfo
{
	char	*key;
	char	*val;
} t_elinfo;

typedef struct s_settings
{
	t_elinfo	*elmap;
	char		*Ntexpath;
	char		*Stexpath;
	char		*Wtexpath;
	char		*Etexpath;
	char		*Floorstr;
	char		*Ceilstr;
	char		**charmap;
} t_settings;

int             check_input(int argc, char **argv);
int	            fileXtract(char *cubflpath);
t_settings	    *read_settings(int openfd);
t_settings      *init_map_settings(int list_size);
int             treat_caught_info(t_elinfo **elinfo, t_list **file_list, int *i);


int	            charmapFree(char **charmap);
void            elmapFree(t_elinfo **map_settings);
void            free_list(t_list **list);
void            free_evaluation(t_settings **map_settings);
void 			free_on_invalid(t_settings *settings);

int	prep_game();
int run_game(t_game game);

# endif