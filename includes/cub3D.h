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

#define ELINFOLIMIT 6
#define RADJUMP 64

#define SQUARESIZE 64

# define MOVESPEED 0.15
# define ROTATESPEED 0.15

#define WALKDIST 10 // pixels every move

#define WINDOWSIZE_X 640
#define WINDOWSIZE_Y 640

#define MINIMAPSIZE_X 160
#define MINIMAPSIZE_Y 160
#define MINIMAPSCALE 1
#define MINIMAPBORDER 8

// #define MinimapLeftRightSquares 4
// #define MinimapTopBotSquares 4
// #define MinimapSquareSize 4
// #define MinimapSquarePixelSize 8

// Shortcuts
#define ppos game->player.pos
#define px game->player.pos.x
#define py game->player.pos.y

# define A 97
# define S 115
# define D 100
# define W 119
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define SPACE 32
# define CTRL 65507
# define SHIFT 65505
# define ESC 65307

# define WALL '1'
# define FLOOR '0'
# define DOOR 'D'

typedef struct s_object t_object;
typedef struct s_game t_game;

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
	int start;
	t_vec2f	pos;
    t_vec2f inv_pos;

    float dirX;
    float dirY;
    float planeX;
    float planeY;
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

typedef struct s_door
{
	int		type;
	int		(*get_image)(t_object *this, int dir);
	void 	(*action)(t_object *this, t_game *game);
	int     state;
	int     x;
	int     y;
} t_door;

struct s_object
{
	int			type;
	int			(*get_image)(t_object *this, int dir);
	void 		(*action)(t_object *this, t_game *game);
};

struct s_game
{
    void		*mlx;
    void		*win;
	t_imgbuffer	imgbuffer;

	t_texture	texture;

	int			minimap_toggle;	
	t_vec2i		mapsize;
    t_vec2i		inv_mapsize;
	char		**charmap;
	t_object	***objmap;
	t_object	*select;
	t_plinfo	player;
};

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
t_plinfo  		prepare_map(t_settings *map_settings);
int				invalid_chars(char **map);

void      		get_maximum_values(t_map_check *maxs, char **map);
char      		**cut_and_define_border(char **map);

void      		get_player(char **map, t_plinfo *player);

int	      		charmapFree(char **charmap);
void      		elmapFree(t_elinfo *map_settings);
void      		free_list(t_list **list);
void      		free_evaluation(t_settings **map_settings);
void 			free_on_invalid(t_settings *settings);

int	      		prep_game(t_settings *map_settings, t_plinfo player);
int 			run_game(t_game *game);

void 			load_textures(t_game *game, t_settings *map_settings);
int 			load_rgb(char *value);
int				rgbtocolor(unsigned char r, unsigned char g, unsigned char b);

int				line(t_game *game, t_vec2i origin, t_vec2i dest, int color);
int				horline(t_game *game, t_vec2i pos, size_t size, int color);
int				verline(t_game *game, t_vec2i pos, size_t size, int color);

void	    	mypixelput(t_imgbuffer *imgbuffer, int x, int y, int color);
int				pixsquare(t_game *game, t_vec2i pos, size_t size, int color);
int				pixsquaref(t_game *game, t_vec2f pos, size_t size, int color);
int				pixsquarecent(t_game *game, t_vec2f pos, size_t size, int color);
void			squarecent_prop(t_game *game, t_vec2f pos, float size, int color);
void			square_prop(t_game *game, t_vec2i pos, size_t size, int color);
void			square_propf(t_game *game, t_vec2f pos, float size, int color);

int				draw_map(t_game *game);
int	      		draw_player(t_game *game);
void 			draw_checkerboard(t_game *game, t_vec2i start, size_t q, size_t pixelsize);
void 			draw_minimap(t_game *game);
void 			draw_crosshair(t_game *game, int size, int color);
void 			draw_ray(t_game *game);
void	    	myclearimg(t_game *game);
int	      		imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y);

t_object 		*new_door(int x, int y);
t_object 		*new_wall();

int 			key_event(int key, t_game *game);

char			coordcheck(t_game *game, int x, int y);
char			coordcheck_prop(t_game *game, int x, int y);


t_vec2f			vec2f(float x, float y);
t_vec2i  		vec2i(int x, int y);;

void 			close_game(t_game *game);

# endif