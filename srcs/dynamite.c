# include "../includes/cub3D.h"

void    load_explosion(t_game *game)
{
    game->explosion.frameNum = 19;
    game->explosion.frames = load_n_images(game, "./explosionFrames/explosion", game->explosion.frameNum);
    game->explosion.current_frame = game->explosion.frames;
    game->explosion.trigger = 0;
    game->explosion.frameCount = 1;

    game->explosion.frameTime = 200000;
    game->explosion.startTime.tv_sec = 0;
    game->explosion.startTime.tv_nsec = 0;
}

static t_imgbuffer  get_image_dynamite(t_dynamite *this, int dir)
{
    (void)dir;
    return (*this->texture);
    // return (this->animation->current_frame->img);
}

static void action_dynamite(t_object **this, t_game *game)
{
    // *this = NULL;
    // game->explosion.trigger = 1;
}

t_object *new_dynamite(t_game *game)
{
    t_dynamite *dynamite;

    dynamite = ft_calloc(sizeof(t_dynamite), 1);
    dynamite->type = DYNAMITE;
    dynamite->get_image = get_image_dynamite;
    dynamite->action = action_dynamite; // TODO: activates the explosion...
    // Time based explosion cant be done because we dont iterate through all objects
    // dynamite->texture = &game->explosion.frames->img;
    dynamite->texture = &game->texture_dynamite;

    dynamite->animation = &game->explosion;

    return ((t_object *)dynamite);
}

/**
 * Go read update_gun for original with comments
*/
void    update_dynamite(t_animation *explosion)
{
    microSeconds td;

    if (explosion->trigger == 0)
        return;
    else if (explosion->trigger == 1 && explosion->frameCount == 1)
    {
        clock_gettime(CLOCK_MONOTONIC, &explosion->startTime);
        explosion->frameCount++;
        return;
    }
    td = timediff(explosion->startTime);
    if (td > explosion->frameTime * (explosion->frameCount - 1))
    {
        explosion->frameCount++;
        explosion->current_frame = explosion->current_frame->next;
        if (explosion->current_frame == NULL)
        {
            explosion->trigger = 0;
            explosion->current_frame = explosion->frames;
            explosion->frameCount = 1;
        }
		printf("AnimationFrame_%d: %ld\n", explosion->frameCount, td);
		return;
	}
    printf("AnimationFrame_%d: %ld\n", explosion->frameCount, td);
}