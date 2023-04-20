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

#define WINDOWSIZE_X 1600
#define WINDOWSIZE_Y 800

#define ELINFOLIMIT 6
#define RADJUMP 32

//Do Not Touch!
#define SQUARESIZE 16
// #define WALKDIST 1
// __

# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307

# define WALL '1'
# define FLOOR '0'

enum e_player_orientation
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
};

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

typedef struct s_map_check
{
	int top;
	int right;
	int left;
	int bottom;
} t_map_check;

typedef struct s_player_check
{
    int north;
    int south;
    int east;
    int west;
} t_player_check;

typedef struct s_texture
{
	t_img	n;
	t_img	s;
	t_img	w;
	t_img	e;
	int		ceil_color;
	int		floor_color;

} t_texture;

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

	t_texture	texture;
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
	t_elinfo	elmap[ELINFOLIMIT];
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
int             treat_caught_info(t_elinfo *elinfo, t_list **file_list, int *i);
t_plinfo  prepare_map(t_settings *map_settings);
int				invalid_chars(char **map);
void      get_maximum_values(t_map_check *maxs, char **map);
char      **cut_and_define_border(char **map);
void      get_player(char **map, t_plinfo *player);

int	      charmapFree(char **charmap);
void      elmapFree(t_elinfo *map_settings);
void      free_list(t_list **list);
void      free_evaluation(t_settings **map_settings);
void 			free_on_invalid(t_settings *settings);

int	      prep_game(t_settings *map_settings, t_plinfo player);
int 			run_game(t_game *game);
void load_textures(t_game *game, t_settings *map_settings);
int load_rgb(char *value);

int				rgbtocolor(unsigned char r, unsigned char g, unsigned char b);
int				line(t_game *game, t_vec2i origin, t_vec2i dest, int color);
int				line_s(t_game *game, t_vec2i origin, size_t size, int color);
int				line_tf(t_game *game, t_vec2f origin, size_t size, int color);
void	    mypixelput(t_imgbuffer *imgbuffer, int x, int y, int color);

int	pixsquare(t_game *game, t_vec2i pos, size_t size, int color);
int	pixsquaref(t_game *game, t_vec2f pos, size_t size, int color);
int	pixsquarecent(t_game *game, t_vec2f pos, size_t size, int color);
void	squarecent_prop(t_game *game, t_vec2f pos, size_t size, int color);
void	square_prop(t_game *game, t_vec2i pos, size_t size, int color);
void	square_propf(t_game *game, t_vec2f pos, size_t size, int color);


int				draw_map(t_game *game);

int				horline(t_game *game, t_vec2i pos, size_t size, int color);
int				verline(t_game *game, t_vec2i pos, size_t size, int color);

int				line_t(t_game *game, t_vec2i origin, size_t size, int color);


char	coordcheck(t_game *game, int x, int y);
int p_move(t_game *game, int ns, int ew);


int	      setstartpos(t_game *game);

int	      imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y);

void	    myclearimg(t_game *game);
int	      draw_player(t_game *game);

int	draw_ray(t_game *game);





# endif