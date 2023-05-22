/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:42:58 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 14:45:59 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>

# define ELINFOLIMIT 6
# define RADJUMP 64
# define SQUARESIZE 64
# define MOVESPEED 0.15
# define ROTATESPEED 0.20
# define ROTDIVIDER 8
# define WINDOWSIZE_X 640
# define WINDOWSIZE_Y 640
# define MINIMAPSIZE_X 160
# define MINIMAPSIZE_Y 160
# define MINIMAPSCALE 1
# define MINIMAPBORDER 8
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
# define STATICENEMY 'T'
# define VALIDSTRING "10NSWEDT"

typedef struct s_game			t_game;
typedef struct s_object			t_object;
typedef struct s_imgbuffer		t_imgbuffer;
typedef struct s_door			t_door;
typedef struct s_wall			t_wall;
typedef struct s_staticenemy	t_staticenemy;

typedef long					t_microseconds;

typedef struct s_start_values
{
	char	*map_name;
	int		mouse_selected;
}	t_start_values;


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
	int	north;
	int	south;
	int	east;
	int	west;
}	t_player_check;

typedef struct s_map_check
{
	int	top;
	int	right;
	int	left;
	int	bottom;
}	t_map_check;

typedef struct s_elinfo
{
	char	*key;
	char	*val;
}	t_elinfo;

typedef struct s_settings
{
	t_elinfo	elmap[ELINFOLIMIT];
	char		*ntexpath;
	char		*stexpath;
	char		*wtexpath;
	char		*etexpath;
	char		*floorstr;
	char		*ceilstr;
	char		**charmap;
}				t_settings;

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
	int		start;
	t_vec2f	pos;
	t_vec2f	inv_pos;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_plinfo;

struct s_imgbuffer
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
};

typedef struct s_texture_sides
{
	t_imgbuffer	n;
	t_imgbuffer	s;
	t_imgbuffer	w;
	t_imgbuffer	e;
}	t_texture_sides;

typedef struct s_anim_list
{
	t_imgbuffer			img;
	struct s_anim_list	*next;
}	t_anim_list;

typedef struct s_animation
{
	int					trigger;
	int					frame_count;
	int					frame_num;
	t_microseconds		frame_time;
	struct timespec		start_time;
	t_anim_list			*frames;
	t_anim_list			*current_frame;
}	t_animation;

struct s_staticenemy
{
	int				type;
	t_imgbuffer		(*get_image)(t_staticenemy *this, int dir);
	void			(*action)(t_object **this, t_game *game);
	t_animation		animation;
	int				state;
};

struct s_door
{
	int				type;
	t_imgbuffer		(*get_image)(t_door *this, int dir);
	void			(*action)(t_object **this, t_game *game);
	t_animation		animation;
	int				state;
	int				x;
	int				y;
	t_imgbuffer		*texture_door_closed;
};

struct s_wall
{
	int				type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void			(*action)(t_object **this, t_game *game);
	t_animation		animation;
	t_texture_sides	*textures;
};


struct s_object
{
	int				type;
	t_imgbuffer		(*get_image)(t_object *this, int dir);
	void			(*action)(t_object **this, t_game *game);
	t_animation		animation;
};

typedef struct s_raycast
{
	int				first_obj_x;
	int				first_obj_y;
	int				block;
	int				x;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				texture_pixels[SQUARESIZE * SQUARESIZE];
}	t_raycast;

struct s_game
{
	void			*mlx;
	void			*win;
	t_imgbuffer		imgbuffer;
	int				mouse_selected;
	int				ceil_color;
	int				floor_color;
	int				minimap_toggle;	
	t_vec2i			mapsize;
	t_vec2i			inv_mapsize;
	char			**charmap;
	t_object		***objmap;
	t_object		**select;
	t_plinfo		player;
	t_texture_sides	texture_wall;
	t_imgbuffer		texture_door;
	t_animation		player_shoot;
	t_animation		capy_walk;
	t_animation		capy_munch;
	struct timespec	now_time;
	struct timespec	old_time;
};


t_start_values		select_map(void);
int					file_extract(t_start_values ret);
t_settings			*read_settings(int openfd);
t_settings			*init_map_settings(int list_size);
int					treat_caught_info(t_elinfo *elinfo, \
	t_list **file_list, int *i);
t_plinfo			prepare_map(t_settings *map_settings);
int					invalid_chars(char **map);
void				get_maximum_values(t_map_check *maxs, char **map);
char				**cut_and_define_border(char **map);
void				get_player(char **map, t_plinfo *player);
int					charmap_free(char **charmap);
void				elmap_free(t_elinfo *map_settings);
void				free_list(t_list **list);
void				free_evaluation(t_settings **map_settings);
void				free_on_invalid(t_settings *settings);
void				player_pos(t_plinfo *player, int x, int y);
int					prep_game(t_settings *map_settings, t_plinfo player, \
	int mouse_selected);
int					run_game(t_game *game);
void				load_textures(t_game *game, t_settings *map_settings);
int					load_rgb(char *value);
int					rgbtocolor(unsigned char r, unsigned char g, \
	unsigned char b);
void				line(t_game *game, t_vec2i origin, t_vec2i dest, int color);
int					horline(t_game *game, t_vec2i pos, size_t size, int color);
int					verline(t_game *game, t_vec2i pos, size_t size, int color);
void				mypixelput(t_imgbuffer *imgbuffer, int x, int y, int color);
int					pixsquare(t_game *game, t_vec2i pos, size_t size, \
	int color);
void				draw_checkerboard(t_game *game, t_vec2i start, size_t q, \
	size_t pixelsize);
void				draw_minimap(t_game *game);
void				draw_crosshair(t_game *game, int size, int color);
void				draw_ray(t_game *game);
void				myclearimg(t_game *game);
int					imgbufferoffset(t_imgbuffer *imgbuffer, int x, int y);
int					rgb_norm(char *str, char **rgb, int *rgbi, int i);
void				object_selector(t_game *game, t_raycast *ray);
void				delta_dist(t_raycast *ray);
void				ray_direction(t_raycast *ray, t_game *game, int x);
void				get_draw_start_end(t_raycast *ray);
void				line_height(t_raycast *ray);
void				load_buffer_array(t_raycast *ray, t_game *game, \
	t_imgbuffer img);
void				wall_texture_position(t_raycast *ray, t_game *game);
void				draw_vertical_stripe(t_game *game, t_raycast *ray);
void				perp_wall_dist(t_raycast *ray, t_game *game);
t_object			*new_door(int x, int y, t_game *game);
t_object			*new_wall(t_game *game);
void				rotate_direction(t_game *game, double angle_x, \
	double angle_y);
int					key_event(int key, t_game *game);
char				coordcheck(t_game *game, int x, int y);
char				coordcheck_prop(t_game *game, int x, int y);
t_anim_list			*load_n_images(t_game *game, char *imagename, \
	int number_of_images);
t_anim_list			*create_frame_node(t_imgbuffer frame);
void				insert_frame(t_anim_list **head, t_imgbuffer frame);
void				free_anim_list(t_game *game, t_anim_list **head);
t_vec2f				vec2f(float x, float y);
t_vec2i				vec2i(int x, int y);
void				close_game(t_game *game);
int					mousemove_capture(int x, int y, void *param);
int					mousedown_capture(int button, int x, int y, void *param);
t_microseconds		timestamp(struct timespec clock);
t_microseconds		timestampdiff(struct timespec new, struct timespec old);
t_microseconds		timediff(struct timespec old);
void				draw_weapon(t_game *game);
void				update_gun(t_animation *gun);
t_object			***load_individual_map_tile(char **map, t_game *game);
void				free_objmap(char **map, t_object ***obj);
void				update_anim(t_animation *anim, t_microseconds tmstmpnow);
int					mypixelget(t_imgbuffer *imgbuffer, int x, int y);
void				update(t_game *game, t_microseconds tmstmpnow);
void				load_capy_walk(t_game *game);
void				load_capy_munch(t_game *game);
t_object			*new_staticenemy(t_game *game);
void				load_pov(t_plinfo *player, float plane_x, float plane_y);
void				load_orientation(t_plinfo *player, int dir_x, int dir_y);
void				define_start_orientation(t_plinfo *player);
void				press_right(t_game *game);
void				press_left(t_game *game);
void				press_back(t_game *game);
void				press_forward(t_game *game);
int					collision(t_game *game, int x, int y);

#endif
