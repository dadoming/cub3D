# include "../includes/cub3D.h"

void	    load_capy_idle(t_game *game)
{
    game->capy_idle.frameNum = 8;
    game->capy_idle.frames = load_n_images(game, "CapySitIdle/capybaraSittingIdle", game->capy_idle.frameNum);
    game->capy_idle.current_frame = game->capy_idle.frames;
    game->capy_idle.trigger = 0;
    game->capy_idle.frameCount = 1;

    game->capy_idle.frameTime = 200000;
    game->capy_idle.startTime.tv_sec = 0;
    game->capy_idle.startTime.tv_nsec = 0;
}

void	load_capy_walk(t_game *game)
{
    game->capy_walk.frameNum = 8;
    game->capy_walk.frames = load_n_images(game, "CapyWalk/capyWalk", game->capy_walk.frameNum);
    game->capy_walk.current_frame = game->capy_walk.frames;
    game->capy_walk.trigger = 0;
    game->capy_walk.frameCount = 1;

    game->capy_walk.frameTime = 100000;
    game->capy_walk.startTime.tv_sec = 0;
    game->capy_walk.startTime.tv_nsec = 0;
}

void    load_capy_munch(t_game *game)
{
    game->capy_munch.frameNum = 8;
    game->capy_munch.frames = load_n_images(game, "CapyMunch/capyMunch", game->capy_munch.frameNum);
    game->capy_munch.current_frame = game->capy_munch.frames;
    game->capy_munch.trigger = 0;
    game->capy_munch.frameCount = 1;

    game->capy_munch.frameTime = 100000;
    game->capy_munch.startTime.tv_sec = 0;
    game->capy_munch.startTime.tv_nsec = 0;
}