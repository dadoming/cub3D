/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:27:12 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:42:23 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/menu.h"

void	open_select_window(t_menu *menu)
{
	printf("Opening select window...\n");
     menu->mlx = mlx_init();
    if (!menu->mlx)
	{
		printf("Error: could not initialize mlx!\n");
        delete_circular_list(&menu->map_list);
		exit(0);
	}
	menu->win = mlx_new_window(menu->mlx, WINDOWSIZE_X, \
		WINDOWSIZE_Y, "Select map");
	if (!menu->win)
	{
		printf("Error: could not create window!\n");
        delete_circular_list(&menu->map_list);
		mlx_destroy_display(menu->mlx);
		free(menu->mlx);
		exit(0);
	}
	mlx_hook(menu->win, 2, 1L << 0, input_event, menu);
	mlx_hook(menu->win, 17, 1L << 2, x_close, menu);
}

void	print_map_list(t_menu *menu, t_map_list *map_list)
{
	clear_img(menu);
	draw_rectangles(menu);
	mlx_put_image_to_window(menu->mlx, menu->win, menu->imgbuffer.img, 0, 0);
	mlx_string_put(menu->mlx, menu->win, 20, 30, YELLOW, \
		"Press arrows and space to move in this menu!");
	mlx_string_put(menu->mlx, menu->win, 20, 100 - 20, YELLOW, "<");
	mlx_string_put(menu->mlx, menu->win, 50, 100 - 20, WHITE, map_list->name);
	mlx_string_put(menu->mlx, menu->win, 275, 100 - 20, YELLOW, ">");
	mlx_string_put(menu->mlx, menu->win, 20, 115, YELLOW, "Mouse: ");
	mlx_string_put(menu->mlx, menu->win, 20, 115 + 25, YELLOW, \
		"(if not selected, only keys will work)");
	mlx_string_put(menu->mlx, menu->win, 20, 170, RED, \
		"Press space on map to start!");
}

static void create_image(t_menu *menu)
{
    if (!menu->imgbuffer.img || !menu->imgbuffer.addr)
    {
        printf("Error: could not create image!\n");
        close_window(menu);
        exit(0);
    }
}

t_start_values	select_map(void)
{
	t_menu			menu;
	t_start_values	ret;

	ft_memset(&ret, 0, sizeof(t_start_values));
	ft_memset(&menu, 0, sizeof(t_menu));
	menu.map_list = get_available_maps();
	if (!menu.map_list)
		return (ret);
	open_select_window(&menu);
	menu.imgbuffer.img = mlx_new_image(menu.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
	menu.imgbuffer.addr = mlx_get_data_addr(menu.imgbuffer.img, \
		&menu.imgbuffer.bits_per_pixel, &menu.imgbuffer.line_length, \
		&menu.imgbuffer.endian);
	create_image(&menu);
	clear_img(&menu);
	menu.current = 1;
	menu.mouse_selected = 1;
	print_map_list(&menu, menu.map_list);
	mlx_loop(menu.mlx);
	ret.map_name = ft_strjoin("./maps/", menu.map_list->name);
	ret.mouse_selected = menu.mouse_selected;
	close_window(&menu);
	printf("Closing select window...\n");
	return (ret);
}
