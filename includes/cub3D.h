# ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
# include <limits.h>
#include <unistd.h>
# include <sys/time.h>
# include <time.h>

#define ELINFOLIMIT 6
#define RADJUMP 64

#define SQUARESIZE 64

# define MOVESPEED 0.20
# define ROTATESPEED 0.20
# define ROTDIVIDER 8

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

# define E 101

# define WALL '1'
# define FLOOR '0'
# define DOOR 'D'
# define DYNAMITE 'Y'
# define STATICENEMY 'T'

#define VALIDSTRING "10NSWEDXKT"

typedef struct s_object t_object;
typedef struct s_game t_game;
typedef struct s_imgbuffer t_imgbuffer;
typedef struct s_door t_door;
typedef struct s_wall t_wall;

typedef long microseconds;

typedef struct s_start_values
{
    char *map_name;
    int mouse_selected;
} t_start_values;


enum e_player_orientation
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum e_door_state
{
    CLOSED,
    OPEN
};

typedef struct s_player_check
{
    int north;
    int south;
    int east;
    int west;
} t_player_check;

typedef struct s_map_check
{
	int top;
	int right;
	int left;
	int bottom;
} t_map_check;

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

    float dir_x;
    float dir_y;
    float planeX;
    float planeY;
} t_plinfo;

struct s_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int     width;
	int     height;
};

typedef struct s_texture_sides
{
    t_imgbuffer n;
    t_imgbuffer s;
    t_imgbuffer w;
    t_imgbuffer e;
} t_texture_sides;

typedef struct s_anim_list
{
    t_imgbuffer img;
    struct s_anim_list *next;
} t_anim_list;

typedef struct s_animation
{
    int trigger; // on or off 
    int frameCount; // present frame
    int frameNum; // number of frames

    microseconds frameTime; // how many frames the animation takes in microSeconds
    struct timespec startTime; // time of last animation change

    t_anim_list *frames;
    t_anim_list *current_frame;
} t_animation;

typedef struct s_staticenemy t_staticenemy;
struct s_staticenemy
{
	int		type;
	t_imgbuffer	(*get_image)(t_staticenemy *this, int dir);
	void 	(*action)(t_object **this, t_game *game);
    t_animation animation;

	int     state;
};

struct s_door
{
	int		type;
	t_imgbuffer	(*get_image)(t_door *this, int dir);
	void 	(*action)(t_object **this, t_game *game);
    t_animation animation;

	int     state;
	int     x;
	int     y;
    t_imgbuffer    *texture_door_opened;
    t_imgbuffer    *texture_door_closed;
};

struct s_wall
{
	int			    type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void 		    (*action)(t_object **this, t_game *game);
    t_animation     animation;
    t_texture_sides	*textures;
};


struct s_object
{
	int			    type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void 		    (*action)(t_object **this, t_game *game);
    t_animation     animation;
};

typedef struct s_raycast
{
    int first_obj_x;
    int first_obj_y;
    int block;

    int x;
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    double wall_x;
    int tex_x;
    double step;
    double tex_pos;
    int texture_pixels[SQUARESIZE * SQUARESIZE];
} t_raycast;

typedef struct s_statTextures
{
    t_texture_sides	texture_wall;
    
    t_imgbuffer	texture_door;
    t_imgbuffer dynamite;
} t_statTextures;

struct s_game
{
    void		*mlx;
    void		*win;
	t_imgbuffer	imgbuffer;
    int mouse_selected;
    
    int		ceil_color;
	int		floor_color;

	int			minimap_toggle;	
	t_vec2i		mapsize;
    t_vec2i		inv_mapsize;
	char		**charmap;

	
    t_object	***objmap;
	t_object	**select;
	t_plinfo	player;

    t_texture_sides	texture_wall;
    
    t_imgbuffer	texture_door;
    t_imgbuffer texture_dynamite;

    t_animation player_shoot;
    t_animation explosion;

    t_animation capy_idle;
    t_animation capy_walk;
    t_animation capy_munch;

    struct timespec now_time;
    struct timespec old_time;
};

#include "functions.h"

#endif