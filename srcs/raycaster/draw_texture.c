/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:52:43 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 19:17:03 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	extract_texture_pixels(t_imgbuffer *texture, int *pixels)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			if (y * texture->width + x > SQUARESIZE * SQUARESIZE)
			{
				printf("Extract texture error\n");
				return ;
			}
			color = mypixelget(texture, x, y);
			if ((color & 0x00FFFFFF) != 0)
				pixels[(y * texture->width) + x] = color;
			x++;
		}
		y++;
	}
}

void	load_buffer_array(t_raycast *ray, t_game *game, t_imgbuffer img)
{
	if (game->objmap[ray->map_x][ray->map_y]->type == STATICENEMY)
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			(game->objmap[ray->map_x][ray->map_y], 0);
	else if (ray->side == 0 && ray->ray_dir_x > 0 && \
		(game->objmap[ray->map_x][ray->map_y]->type != DOOR))
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			(game->objmap[ray->map_x][ray->map_y], WEST);
	else if (ray->side == 0 && ray->ray_dir_x < 0 && \
		(game->objmap[ray->map_x][ray->map_y]->type != DOOR))
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			(game->objmap[ray->map_x][ray->map_y], EAST);
	else if (ray->side == 1 && ray->ray_dir_y > 0 && \
		(game->objmap[ray->map_x][ray->map_y]->type != DOOR))
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			(game->objmap[ray->map_x][ray->map_y], SOUTH);
	else if (ray->side == 1 && ray->ray_dir_y < 0 && \
		(game->objmap[ray->map_x][ray->map_y]->type != DOOR))
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			(game->objmap[ray->map_x][ray->map_y], NORTH);
	else if (game->objmap[ray->map_x][ray->map_y]->type == DOOR \
		&& ((t_door *)game->objmap[ray->map_x][ray->map_y])->state == 0)
		img = game->objmap[ray->map_x][ray->map_y]->get_image \
			((t_object *)(game->objmap[ray->map_x][ray->map_y]), 0);
	extract_texture_pixels(&img, ray->texture_pixels);
}

void	wall_texture_position(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wall_x = game->player.inv_pos.y + \
			ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = game->player.inv_pos.x + \
			ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)SQUARESIZE);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = SQUARESIZE - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = SQUARESIZE - ray->tex_x - 1;
	ray->step = 1.0 * SQUARESIZE / ray->line_height;
	ray->tex_pos = (ray->draw_start - WINDOWSIZE_Y / 2 \
		+ ray->line_height / 2) * ray->step;
	load_buffer_array(ray, game, (t_imgbuffer){0});
}

int	draw_sky(t_game *game, t_raycast *ray)
{
	int	j;

	j = 0;
	while (j < ray->draw_start)
	{
		mypixelput(&game->imgbuffer, ray->x, j, game->ceil_color);
		j++;
	}
	return (j);
}

void	draw_vertical_stripe(t_game *game, t_raycast *ray)
{
	int	y;
	int	j;
	int	tex_y;
	int	color;

	y = ray->draw_start;
	j = draw_sky(game, ray);
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (SQUARESIZE - 1);
		ray->tex_pos += ray->step;
		color = ray->texture_pixels[SQUARESIZE * tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		mypixelput(&game->imgbuffer, ray->x, y, color);
		y++;
		j++;
	}
	while (j < WINDOWSIZE_Y - 1)
	{
		mypixelput(&game->imgbuffer, ray->x, j, game->floor_color);
		j++;
	}
}
