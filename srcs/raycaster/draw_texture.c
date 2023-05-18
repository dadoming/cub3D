/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:52:43 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 22:37:40 by dadoming         ###   ########.fr       */
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
	if (game->objmap[ray->mapX][ray->mapY]->type == STATICENEMY)
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			(game->objmap[ray->mapX][ray->mapY], 0);
	else if (ray->side == 0 && ray->ray_dir_x > 0 && \
		(game->objmap[ray->mapX][ray->mapY]->type != DOOR))
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			(game->objmap[ray->mapX][ray->mapY], WEST);
	else if (ray->side == 0 && ray->ray_dir_x < 0 && \
		(game->objmap[ray->mapX][ray->mapY]->type != DOOR))
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			(game->objmap[ray->mapX][ray->mapY], EAST);
	else if (ray->side == 1 && ray->ray_dir_y > 0 && \
		(game->objmap[ray->mapX][ray->mapY]->type != DOOR))
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			(game->objmap[ray->mapX][ray->mapY], SOUTH);
	else if (ray->side == 1 && ray->ray_dir_y < 0 && \
		(game->objmap[ray->mapX][ray->mapY]->type != DOOR))
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			(game->objmap[ray->mapX][ray->mapY], NORTH);
	else if (game->objmap[ray->mapX][ray->mapY]->type == DOOR \
		&& ((t_door *)game->objmap[ray->mapX][ray->mapY])->state == 0)
		img = game->objmap[ray->mapX][ray->mapY]->get_image \
			((t_object *)(game->objmap[ray->mapX][ray->mapY]), 0);
	extract_texture_pixels(&img, ray->texture_pixels);
}

void	wall_texture_position(t_raycast *ray, t_game *game)
{
	if (ray->side == 0)
		ray->wallX = game->player.inv_pos.y + ray->perpWallDist * ray->ray_dir_y;
	else
		ray->wallX = game->player.inv_pos.x + ray->perpWallDist * ray->ray_dir_x;
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (double)SQUARESIZE);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->texX = SQUARESIZE - ray->texX - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->texX = SQUARESIZE - ray->texX - 1;
	ray->step = 1.0 * SQUARESIZE / ray->lineHeight;
	ray->texPos = (ray->drawStart - WINDOWSIZE_Y / 2 \
		+ ray->lineHeight / 2) * ray->step;
	load_buffer_array(ray, game, (t_imgbuffer){0});
}

int	draw_sky(t_game *game, t_raycast *ray)
{
	int	j;

	j = 0;
	while (j < ray->drawStart)
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

	y = ray->drawStart;
	j = draw_sky(game, ray);
	while (y < ray->drawEnd)
	{
		tex_y = (int)ray->texPos & (SQUARESIZE - 1);
		ray->texPos += ray->step;
		color = ray->texture_pixels[SQUARESIZE * tex_y + ray->texX];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		mypixelput(&game->imgbuffer, ray->x, y, color);
		y++;
		j++;
	}
	while (j < WINDOWSIZE_Y)
	{
		mypixelput(&game->imgbuffer, ray->x, j, game->floor_color);
		j++;
	}
}
