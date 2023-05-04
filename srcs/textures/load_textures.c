# include "../../includes/cub3D.h"

t_imgbuffer load_texture(t_game *game, char *path)
{
    t_imgbuffer texture;

    texture.img = mlx_xpm_file_to_image(game->mlx, path, &(texture.width), &(texture.height));
    texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
    return (texture);
}

static int load_textures_to_mlx(t_game *game, t_settings *map_settings)
{
    game->texture.n = load_texture(game->mlx, map_settings->Ntexpath);
    game->texture.s = load_texture(game->mlx, map_settings->Stexpath);
    game->texture.w = load_texture(game->mlx, map_settings->Wtexpath);
    game->texture.e = load_texture(game->mlx, map_settings->Etexpath);
    if ((game->texture.n.img == NULL) \
     || (game->texture.s.img == NULL) \
     || (game->texture.w.img == NULL) \
     || (game->texture.e.img == NULL))
    {
        printf("%p %p %p %p\n", game->texture.n.img, game->texture.s.img, game->texture.w.img, game->texture.e.img);
        printf("Error\nInvalid texture path\n");
        return (1);
    }
    return (0);
}

static void free_textures(t_game *game)
{
    if (game->texture.n.img)
        mlx_destroy_image(game->mlx, game->texture.n.img);
    if (game->texture.s.img)
        mlx_destroy_image(game->mlx, game->texture.s.img);
    if (game->texture.w.img)
        mlx_destroy_image(game->mlx, game->texture.w.img);
    if (game->texture.e.img)
        mlx_destroy_image(game->mlx, game->texture.e.img);
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
    game->texture.ceil_color = load_rgb(map_settings->Ceilstr); 
    if (game->texture.ceil_color == -1)
    {
        printf("Error\nInvalid RGB value\n");
        free_textures(game);
        free_on_invalid(map_settings);
    }
    game->texture.floor_color = load_rgb(map_settings->Floorstr);
    if (game->texture.floor_color == -1)
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
    printf("Ceiling color: %d\n", game->texture.ceil_color);
    printf("Floor color: %d\n", game->texture.floor_color);
}