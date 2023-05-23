/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capybara.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:30:47 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/23 11:05:49 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	load_capy_walk(t_game *game)
{
	game->capy_walk.frame_num = 8;
	game->capy_walk.frames = load_n_images(game, \
		"CapyWalk/capyWalk", game->capy_walk.frame_num);
	game->capy_walk.current_frame = game->capy_walk.frames;
	game->capy_walk.trigger = 0;
	game->capy_walk.frame_count = 1;
	game->capy_walk.frame_time = 100000;
	game->capy_walk.start_time.tv_sec = 0;
	game->capy_walk.start_time.tv_nsec = 0;
}

void	load_capy_munch(t_game *game)
{
	game->capy_munch.frame_num = 8;
	game->capy_munch.frames = load_n_images(game, \
		"CapyMunch/capyMunch", game->capy_munch.frame_num);
	game->capy_munch.current_frame = game->capy_munch.frames;
	game->capy_munch.trigger = 0;
	game->capy_munch.frame_count = 1;
	game->capy_munch.frame_time = 100000;
	game->capy_munch.start_time.tv_sec = 0;
	game->capy_munch.start_time.tv_nsec = 0;
}
