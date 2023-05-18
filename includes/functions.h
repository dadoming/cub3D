#pragma once

t_start_values select_map(void);
int check_input(int argc, char **argv);
int	fileXtract(t_start_values ret);
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

int prep_game(t_settings *map_settings, t_plinfo player, int mouse_selected);
int run_game(t_game *game);

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

void rotate_direction(t_game *game, double angle_x, double angle_y);
int key_event(int key, t_game *game);

char			coordcheck(t_game *game, int x, int y);
char			coordcheck_prop(t_game *game, int x, int y);

t_anim_list *load_n_images(t_game *game, char *imagename, int number_of_images);
t_anim_list *create_frame_node(t_imgbuffer frame);
void insert_frame(t_anim_list **head, t_imgbuffer frame);
void free_anim_list(t_game *game, t_anim_list **head);

t_vec2f vec2f(float x, float y);
t_vec2i  		vec2i(int x, int y);;

void 			close_game(t_game *game);

int mousemove_capture(int x, int y, void *param);
int mousedown_capture(int button, int x, int y, void *param);

microSeconds timestamp(struct timespec clock);
microSeconds timestampdiff(struct timespec new, struct timespec old);
microSeconds timediff(struct timespec old);

void draw_weapon(t_game *game);
void update_gun(t_animation *gun);

void update_anim(t_animation *anim, microSeconds tmstmpnow);

int mypixelget(t_imgbuffer *imgbuffer, int x, int y);

t_object *new_dynamite(t_game *game);
void update_dynamite(t_animation *explosion);
void load_explosion(t_game *game);

void action_nothing(t_object **this, t_game *game);
t_imgbuffer image_nothing(t_object *this, int dir);

void update(t_game *game, microSeconds tmstmpnow);

void load_capy_idle(t_game *game);
void load_capy_walk(t_game *game);
void load_capy_munch(t_game *game);

t_object *new_staticenemy(t_game *game);


