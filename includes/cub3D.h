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
#include <math.h>
# include <limits.h>
#include <unistd.h>

#define WINDOWSIZE_X 800
#define WINDOWSIZE_Y 500

#define ELINFOLIMIT 6 //TODO: remove artificial limit
#define RADJUMP 32
#define SQUARESIZE 5

#define WALKDIST 5


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

typedef struct s_plinfo
{
	t_vec2f	pos;
	double	theta;

} t_plinfo;

typedef struct s_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_imgbuffer;

typedef struct s_game
{
    void		*mlx;
    void		*win;
	t_imgbuffer	imgbuffer;

	char		**charmap;

	t_plinfo	player;
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
int run_game(t_game *game);

int	rgbtocolor(unsigned char r, unsigned char g, unsigned char b);
void	mypixelput(t_imgbuffer *imgbuffer, int x, int y, int color);

int	line(t_game *game, t_vec2i origin, t_vec2i dest, int color);
int	line_s(t_game *game, t_vec2i origin, size_t size, int color);
int	line_tf(t_game *game, t_vec2f origin, size_t size, int color);

int	pixsquare(t_game *game, t_vec2i pos, size_t size, int color);
int	pixsquaref(t_game *game, t_vec2f pos, size_t size, int color);
int	pixsquarecent(t_game *game, t_vec2f pos, size_t size, int color);

int	draw_map(t_game *game);

int	horline(t_game *game, t_vec2i pos, size_t size, int color);
int	verline(t_game *game, t_vec2i pos, size_t size, int color);

int	line_t(t_game *game, t_vec2i origin, size_t size, int color);

int p_move(t_game *game, int ns, int ew);
int p_movefrwd(t_game *game);
int p_movebkwd(t_game *game);

int	setstartpos(t_game *game);

int	imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y);




# endif