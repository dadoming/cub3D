/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:50:55 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 14:50:32 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	close_game(t_game *game)
{
	if (game->objmap)
		free_objmap(game->charmap, game->objmap);
	if (game->charmap)
        charmap_free(game->charmap);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	
    // insert all textures here
    if (game->imgbuffer.img)
		mlx_destroy_image(game->mlx, game->imgbuffer.img);
	if (game->texture_wall.n.img)
		mlx_destroy_image(game->mlx, game->texture_wall.n.img);
	if (game->texture_wall.s.img)
		mlx_destroy_image(game->mlx, game->texture_wall.s.img);
	if (game->texture_wall.w.img)
		mlx_destroy_image(game->mlx, game->texture_wall.w.img);
	if (game->texture_wall.e.img)
		mlx_destroy_image(game->mlx, game->texture_wall.e.img);
	if (game->texture_door.img)
		mlx_destroy_image(game->mlx, game->texture_door.img);
	if (game->player_shoot.frames)
		free_anim_list(game, &game->player_shoot.frames);
	if (game->capy_walk.frames)
		free_anim_list(game, &game->capy_walk.frames);
	if (game->capy_munch.frames)
		free_anim_list(game, &game->capy_munch.frames);
    if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}

int	x_close_window(t_game *game)
{
	close_game(game);
	return (0);
}

//		mlx_mouse_hide(game->mlx, game->win); ---> this gives mlx leaks
static void	init_game_settings(t_game *game, t_settings *map_settings, \
	t_plinfo player, int mouse_selected)
{
	game->charmap = map_settings->charmap;
	load_textures(game, map_settings);
	game->objmap = load_individual_map_tile(game->charmap, game);
	game->player = player;
	game->minimap_toggle = 0;
	game->mapsize.x = ft_strlen(game->charmap[0]);
	game->mapsize.y = ft_mtrxlen((void **)game->charmap);
	define_start_orientation(&game->player);
	game->player.inv_pos.x = player.pos.x;
	game->player.inv_pos.y = player.pos.y;
	game->inv_mapsize.x = game->mapsize.y;
	game->inv_mapsize.y = game->mapsize.x;
	game->win = mlx_new_window(game->mlx, WINDOWSIZE_X, WINDOWSIZE_Y, "cub3D");
	mlx_hook(game->win, 17, 1L << 2, x_close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_event, game);
	game->mouse_selected = mouse_selected;
	if (mouse_selected)
	{
		mlx_mouse_move(game->mlx, game->win, \
			WINDOWSIZE_X / 2, WINDOWSIZE_Y / 2);
		//mlx_mouse_hide(game->mlx, game->win);
		mlx_hook(game->win, 6, 1L << 6, mousemove_capture, game);
		mlx_hook(game->win, 4, 1L << 6, mousedown_capture, game);
	}
	clock_gettime(CLOCK_MONOTONIC, &game->old_time);
}

static void init_null_game(t_game *game)
{
    game->mlx = NULL;
    game->win = NULL;
    game->objmap = NULL;
    game->charmap = NULL;
    game->select = NULL;
    
    // insert all textures here
    
    //...
}

int	prep_game(t_settings *map_settings, t_plinfo player, int mouse_selected)
{
	t_game	game;

    init_null_game(&game);
	game.mlx = mlx_init();
	if (!game.mlx)
		close_game(&game);
	init_game_settings(&game, map_settings, player, mouse_selected);
	game.imgbuffer.img = mlx_new_image(game.mlx, WINDOWSIZE_X, WINDOWSIZE_Y);
	game.imgbuffer.addr = mlx_get_data_addr(game.imgbuffer.img, &game.imgbuffer.\
		bits_per_pixel, &game.imgbuffer.line_length, &game.imgbuffer.endian);
	if (!game.imgbuffer.img)
		close_game(&game);
	return (run_game(&game));
}
