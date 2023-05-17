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

typedef struct s_object t_object;
typedef struct s_game t_game;
typedef struct s_imgbuffer t_imgbuffer;
typedef struct s_door t_door;

typedef long microSeconds;

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

    float dirX;
    float dirY;
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

    microSeconds frameTime; // how many frames the animation takes in microSeconds
    struct timespec startTime; // time of last animation change

    t_anim_list *frames;
    t_anim_list *current_frame;
} t_animation;

typedef struct s_dynamite t_dynamite;
struct s_dynamite
{
	int			    type;
	t_imgbuffer		(*get_image)(t_dynamite *this, int dir);
	void 		    (*action)(t_object **this, t_game *game);
    t_imgbuffer     *texture;
    t_animation     *animation;
};

struct s_door
{
	int		type;
	t_imgbuffer	(*get_image)(t_door *this, int dir);
	void 	(*action)(t_object **this, t_game *game);
	int     state;
	int     x;
	int     y;
    t_imgbuffer    *texture_door_opened;
    t_imgbuffer    *texture_door_closed;

    // t_imgbuffer *texture;
    t_animation *animation;
};

struct s_object
{
	int			    type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void 		    (*action)(t_object **this, t_game *game);
    t_texture_sides	*textures;
};

typedef struct s_raycast
{
    int first_obj_X;
    int first_obj_Y;
    int block;

    int x;
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit;
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double wallX;
    int texX;
    double step;
    double texPos;
    int texture_pixels[SQUARESIZE * SQUARESIZE];
} t_raycast;

typedef struct s_statTextures
{
    t_texture_sides	texture_wall;
    
    t_imgbuffer	texture_door;
    t_imgbuffer	texture_transparent;
    t_imgbuffer dynamite;
} t_statTextures;

struct s_game
{
    void		*mlx;
    void		*win;
	t_imgbuffer	imgbuffer;
    
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
    t_imgbuffer	texture_transparent;
    t_imgbuffer texture_dynamite;

    t_animation player_shoot;
    t_animation explosion;

    t_animation capy_idle;
    t_animation capy_walk;

    struct timespec now_time;
    struct timespec old_time;
};

#include "functions.h"

#endif