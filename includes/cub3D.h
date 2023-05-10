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

# define WALL '1'
# define FLOOR '0'
# define DOOR 'D'

typedef struct s_object t_object;
typedef struct s_game t_game;
typedef struct s_imgbuffer t_imgbuffer;
typedef struct s_door t_door;

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

struct s_door
{
	int		type;
	t_imgbuffer	(*get_image)(t_door *this, int dir);
	void 	(*action)(t_object *this, t_game *game);
	int     state;
	int     x;
	int     y;
    t_imgbuffer    *texture_door_opened;
    t_imgbuffer    *texture_door_closed;
    //t_texture_animation animation;
};

struct s_object
{
	int			    type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void 		    (*action)(t_object *this, t_game *game);
    t_texture_sides	*texture;
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
    t_anim_list *frames;
    t_anim_list *current_frame;
} t_animation;

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
	t_object	*select;
	t_plinfo	player;

    t_texture_sides	texture_wall;
    
    t_imgbuffer	texture_door;
    t_imgbuffer	texture_transparent;

    t_animation player_animation;
};

char            *select_map(void);
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

void object_selector(t_game *game, t_raycast *ray);
void delta_dist(t_raycast *ray);
void ray_direction(t_raycast *ray, t_game *game, int x);
void get_draw_start_end(t_raycast *ray);
void line_height(t_raycast *ray);
void load_buffer_array(t_raycast *ray, t_game *game);
void wall_texture_position(t_raycast *ray, t_game *game);
void draw_vertical_stripe(t_game *game, t_raycast *ray);
void perp_wall_dist(t_raycast *ray, t_game *game);

t_object *new_door(int x, int y, t_game *game);
t_object *new_wall(t_game *game);

int 			key_event(int key, t_game *game);

char			coordcheck(t_game *game, int x, int y);
char			coordcheck_prop(t_game *game, int x, int y);

t_anim_list *load_n_images(t_game *game, char *imagename, int number_of_images);
t_anim_list *create_frame_node(t_imgbuffer frame);
void insert_frame(t_anim_list **head, t_imgbuffer frame);
void free_anim_list(t_game *game, t_anim_list **head);

t_vec2f vec2f(float x, float y);
t_vec2i  		vec2i(int x, int y);;

void 			close_game(t_game *game);

# endif