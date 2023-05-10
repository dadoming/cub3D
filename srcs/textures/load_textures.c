# include "../../includes/cub3D.h"

//t_imgbuffer load_texture(t_game *game, char *path)
//{
//    t_imgbuffer texture;
//
//    texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
//    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
//    return (texture);
//}

void load_player(t_game *game)
{
    game->player_animation.frameNum = 16;
    game->player_animation.frames = load_n_images(game, "gun", game->player_animation.frameNum);
    game->player_animation.current_frame = game->player_animation.frames;
    game->player_animation.trigger = 0;
    game->player_animation.frameCount = game->player_animation.frameNum;
    //game->player_animation.frames.img = mlx_xpm_file_to_image(game->mlx, "./textures/gun1.xpm", &game->player_animation.frames.width, &game->player_animation.frames.height);    
    //game->player_animation.frames.addr = mlx_get_data_addr(game->player_animation.frames.img, &game->player_animation.frames.bits_per_pixel, &game->player_animation.frames.line_length, &game->player_animation.frames.endian);

}

static int load_textures_to_mlx(t_game *game, t_settings *map_settings)
{
    //game->texture_wall.n = load_texture(game->mlx, map_settings->Ntexpath);
    //game->texture_wall.s = load_texture(game->mlx, map_settings->Stexpath);
    //game->texture_wall.w = load_texture(game->mlx, map_settings->Wtexpath);
    //game->texture_wall.e = load_texture(game->mlx, map_settings->Etexpath);    
    game->texture_wall.n.img = mlx_xpm_file_to_image(game->mlx, map_settings->Ntexpath, &game->texture_wall.n.width, &game->texture_wall.n.height);
    game->texture_wall.n.addr = mlx_get_data_addr(game->texture_wall.n.img, &game->texture_wall.n.bits_per_pixel, &game->texture_wall.n.line_length, &game->texture_wall.n.endian);
    game->texture_wall.s.img = mlx_xpm_file_to_image(game->mlx, map_settings->Stexpath, &game->texture_wall.s.width, &game->texture_wall.s.height);
    game->texture_wall.s.addr = mlx_get_data_addr(game->texture_wall.s.img, &game->texture_wall.s.bits_per_pixel, &game->texture_wall.s.line_length, &game->texture_wall.s.endian);
    game->texture_wall.w.img = mlx_xpm_file_to_image(game->mlx, map_settings->Wtexpath, &game->texture_wall.w.width, &game->texture_wall.w.height);
    game->texture_wall.w.addr = mlx_get_data_addr(game->texture_wall.w.img, &game->texture_wall.w.bits_per_pixel, &game->texture_wall.w.line_length, &game->texture_wall.w.endian);
    game->texture_wall.e.img = mlx_xpm_file_to_image(game->mlx, map_settings->Etexpath, &game->texture_wall.e.width, &game->texture_wall.e.height);
    game->texture_wall.e.addr = mlx_get_data_addr(game->texture_wall.e.img, &game->texture_wall.e.bits_per_pixel, &game->texture_wall.e.line_length, &game->texture_wall.e.endian);
    
    game->texture_door.img = mlx_xpm_file_to_image(game->mlx, "./textures/capybara.xpm", &game->texture_door.width, &game->texture_door.height);
    game->texture_door.addr = mlx_get_data_addr(game->texture_door.img, &game->texture_door.bits_per_pixel, &game->texture_door.line_length, &game->texture_door.endian);
    
    game->texture_transparent.img = mlx_xpm_file_to_image(game->mlx, "./textures/black.xpm", &game->texture_transparent.width, &game->texture_transparent.height);
    game->texture_transparent.addr = mlx_get_data_addr(game->texture_transparent.img, &game->texture_transparent.bits_per_pixel, &game->texture_transparent.line_length, &game->texture_transparent.endian);
    
    load_player(game);
    if ((game->texture_wall.n.img == NULL) || (game->texture_wall.s.img == NULL) || (game->texture_wall.w.img == NULL) || (game->texture_wall.e.img == NULL) || (game->texture_door.img == NULL) || (game->texture_transparent.img == NULL))

    {
        printf("%p %p %p %p\n", game->texture_wall.n.img, game->texture_wall.s.img, game->texture_wall.w.img, game->texture_wall.e.img);
        printf("Error\nInvalid texture path\n");
        return (1);
    }
    return (0);
}

static void free_textures(t_game *game)
{
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
    if (game->texture_transparent.img)
        mlx_destroy_image(game->mlx, game->texture_transparent.img);
    if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void load_textures(t_game *game, t_settings *map_settings)
{
    if (load_textures_to_mlx(game, map_settings))
    {
        free_textures(game);
        free_on_invalid(map_settings);
    }
    game->ceil_color = load_rgb(map_settings->Ceilstr); 
    if (game->ceil_color == -1)
    {
        printf("Error\nInvalid RGB value\n");
        free_textures(game);
        free_on_invalid(map_settings);
    }
    game->floor_color = load_rgb(map_settings->Floorstr);
    if (game->floor_color == -1)
    {
        printf("Error\nInvalid RGB value\n");
        free_textures(game);
        free_on_invalid(map_settings);
    }
    free(map_settings->Ntexpath);
    free(map_settings->Stexpath);
    free(map_settings->Wtexpath);
    free(map_settings->Etexpath);
    free(map_settings->Ceilstr);
    free(map_settings->Floorstr);
    free(map_settings);
    printf("Textures loaded\n");
    printf("Ceiling color: %d\n", game->ceil_color);
    printf("Floor color: %d\n", game->floor_color);
}
