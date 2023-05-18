# include "../../includes/cub3D.h"

t_imgbuffer load_texture(t_game *game, char *path)
{
   t_imgbuffer texture;

   texture.img = mlx_xpm_file_to_image(game->mlx, path, &texture.width, &texture.height);
   if (texture.img != NULL)
        texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
   return (texture);
}

void load_player(t_game *game)
{
    game->player_shoot.frameNum = 16;
    game->player_shoot.frames = load_n_images(game, "gun", game->player_shoot.frameNum);
    game->player_shoot.current_frame = game->player_shoot.frames;
    game->player_shoot.trigger = 0;
    game->player_shoot.frameCount = 1;
    game->player_shoot.frameTime = 100000;
    game->player_shoot.startTime.tv_sec = 0;
    game->player_shoot.startTime.tv_nsec = 0;
}

static int load_textures_to_mlx(t_game *game, t_settings *map_settings)
{
    game->texture_wall.n = load_texture(game, map_settings->Ntexpath);
    game->texture_wall.s = load_texture(game, map_settings->Stexpath);
    game->texture_wall.w = load_texture(game, map_settings->Wtexpath);
    game->texture_wall.e = load_texture(game, map_settings->Etexpath);    
    game->texture_door = load_texture(game, "./textures/capybara.xpm");

    game->texture_transparent = load_texture(game, "./textures/black.xpm");

    game->texture_dynamite = load_texture(game, "./textures/dynamite.xpm");

    load_capy_idle(game);
    load_capy_walk(game);
    load_capy_munch(game);

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
