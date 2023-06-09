/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:21:15 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 01:24:30 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

# include <dirent.h>
# include <stdio.h>
# include <stdlib.h>
# include "../minilibx-linux/mlx.h"
# include  "../libft/libft.h"

# define WINDOWSIZE_X 300
# define WINDOWSIZE_Y 200
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define SPACE 32
# define PURPLE 0x00A020F0
# define YELLOW 0x00FFFF00
# define RED 0x00FF0000
# define WHITE 0x00FFFFFF

// circular doubly linked list
typedef struct s_map_list
{
	char				*name;
	struct s_map_list	*next;
	struct s_map_list	*prev;
}	t_map_list;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_start_values
{
	char	*map_name;
	int		mouse_selected;
}	t_start_values;

typedef struct s_menu
{
	void			*mlx;
	void			*win;
	t_img			imgbuffer;
	t_map_list		*map_list;
	int				current;
	int				mouse_selected;
}	t_menu;

t_map_list		*create_node(char *name);
void			insert_at_beggining(t_map_list **head, t_map_list *node);
void			insert_at_end(t_map_list **head, t_map_list *node);
void			delete_node(t_map_list **head, t_map_list *node);
void			delete_circular_list(t_map_list **head);
int				input_event(int keycode, t_menu *menu);
int				x_close(t_menu *menu);
t_map_list		*get_available_maps(void);
t_map_list		*load_map_list(void);
void			close_window(t_menu *menu);
int				x_close(t_menu *menu);
t_start_values	select_map(void);
void			print_map_list(t_menu *menu, t_map_list *map_list);
void			my_pput(t_img *imgbuffer, int x, int y, int color);
void			clear_img(t_menu *menu);
int				imgbuf_offset(t_img *imgbuffer, int x, int y);
void			draw_rectangle(t_menu *menu, int x_one, int x_two, int y_min);
void			draw_rectangle_mouse(t_menu *menu, int x_one, \
	int x_two, int y_min);
void			draw_rectangles(t_menu *menu);

#endif