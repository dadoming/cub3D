/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 22:59:08 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 18:30:27 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_imgbuffer	load_texture(t_game *game, char *path)
{
	t_imgbuffer	texture;

	texture.img = mlx_xpm_file_to_image(game->mlx, path, \
		&texture.width, &texture.height);
	if (texture.img != NULL)
		texture.addr = mlx_get_data_addr(texture.img, \
		&texture.bits_per_pixel, &texture.line_length, &texture.endian);
	return (texture);
}

void	load_player(t_game *game)
{
	game->player_shoot.frame_num = 16;
	game->player_shoot.frames = load_n_images(game, "Gun/gun", \
		game->player_shoot.frame_num);
	game->player_shoot.current_frame = game->player_shoot.frames;
	game->player_shoot.trigger = 0;
	game->player_shoot.frame_count = 1;
	game->player_shoot.frame_time = 85000;
	game->player_shoot.start_time.tv_sec = 0;
	game->player_shoot.start_time.tv_nsec = 0;
}

int	no_images_or_no_h64_w64(t_game *game)
{
	if ((game->texture_wall.n.img == NULL) || \
		(game->texture_wall.s.img == NULL) || \
		(game->texture_wall.w.img == NULL) || \
		(game->texture_wall.e.img == NULL) || \
		(game->texture_door.img == NULL) || \
		(game->player_shoot.frames == NULL) || \
		(game->capy_walk.frames == NULL) || \
		(game->capy_munch.frames == NULL) || \
		(game->texture_wall.n.height != 64 || \
		game->texture_wall.n.width != 64) || \
		(game->texture_wall.s.height != 64 || \
		game->texture_wall.s.width != 64) || \
		(game->texture_wall.e.height != 64 || \
		game->texture_wall.e.width != 64) || \
		(game->texture_wall.w.height != 64 || \
		game->texture_wall.w.width != 64))
		return (1);
	return (0);
}

static int	load_textures_to_mlx(t_game *game, t_settings *map_settings)
{
	game->texture_wall.n = load_texture(game, map_settings->etexpath);
	game->texture_wall.s = load_texture(game, map_settings->wtexpath);
	game->texture_wall.w = load_texture(game, map_settings->ntexpath);
	game->texture_wall.e = load_texture(game, map_settings->stexpath);
	game->texture_door = load_texture(game, "./textures/DOOR_1E.xpm");
	load_capy_walk(game);
	load_capy_munch(game);
	load_player(game);
	if (no_images_or_no_h64_w64(game))
	{
		printf("Error\nInvalid texture path or texture size\n");
		return (1);
	}
	return (0);
}

void	load_textures(t_game *game, t_settings *map_settings)
{
	if (load_textures_to_mlx(game, map_settings))
	{
		free_map_settings_no_exit(map_settings);
		close_game(game);
	}
	game->ceil_color = load_rgb(map_settings->ceilstr);
	if (game->ceil_color == -1)
	{
		printf("Error\nInvalid RGB value\n");
		free_map_settings_no_exit(map_settings);
		close_game(game);
	}
	game->floor_color = load_rgb(map_settings->floorstr);
	if (game->floor_color == -1)
	{
		printf("Error\nInvalid RGB value\n");
		free_map_settings_no_exit(map_settings);
		close_game(game);
	}
	free_paths(map_settings);
	printf("Textures loaded\n");
}
