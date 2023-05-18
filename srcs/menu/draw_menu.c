/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:41:54 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:52:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/menu.h"

void	draw_rectangle(t_menu *menu, int x_one, int x_two, int y_min)
{
	int	y_max;
	int	left;

	left = x_one;
	if (y_min < 90)
		y_max = 90;
	else
		y_max = 130;
	while (y_min < y_max)
	{
		while (left < x_two)
		{
			my_pput(&menu->imgbuffer, left, y_min, PURPLE);
			left++;
		}
		left = x_one;
		y_min++;
	}
}

void	draw_rectangle_mouse(t_menu *menu, int x_one, int x_two, int y_min)
{
	int	y_max;
	int	aux;
	int	left;

	y_max = 125;
	aux = y_min;
	left = x_one;
	while (y_min < y_max)
	{
		while (left < x_two)
		{
			if (left == x_one || left == x_two - 1 \
				|| y_min == y_max - 1 || y_min == aux)
			{
				my_pput(&menu->imgbuffer, left, y_min, YELLOW);
			}
			else if (menu->mouse_selected == 1)
			{
				my_pput(&menu->imgbuffer, left, y_min, RED);
			}
			left++;
		}
		left = x_one;
		y_min++;
	}
}

void	draw_rectangles(t_menu *menu)
{
	if (menu->current == 0)
		draw_rectangle(menu, 15, 30, 65);
	else if (menu->current == 2)
		draw_rectangle(menu, 265, 285, 65);
	else if (menu->current == 1)
		draw_rectangle(menu, 30, 265, 65);
	else if (menu->current == 3)
		draw_rectangle(menu, 60, 95, 95);
	draw_rectangle_mouse(menu, 65, 90, 100);
}
