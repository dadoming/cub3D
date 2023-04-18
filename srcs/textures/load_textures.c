# include "../../includes/cub3D.h"

static int load_textures_to_mlx(t_game *game, t_settings *map_settings)
{
    game->texture.n.ptr = mlx_xpm_file_to_image(game->mlx, map_settings->Ntexpath, &(game->texture.n.width), &(game->texture.n.height));
    game->texture.s.ptr = mlx_xpm_file_to_image(game->mlx, map_settings->Stexpath, &(game->texture.s.width), &(game->texture.s.height));
    game->texture.w.ptr = mlx_xpm_file_to_image(game->mlx, map_settings->Wtexpath, &(game->texture.w.width), &(game->texture.w.height));
    printf("%s\n", map_settings->Etexpath);
    game->texture.e.ptr = mlx_xpm_file_to_image(game->mlx, map_settings->Etexpath, &(game->texture.e.width), &(game->texture.e.height));
    if ((game->texture.n.ptr == NULL) \
     || (game->texture.s.ptr == NULL) \
     || (game->texture.w.ptr == NULL) \
     || (game->texture.e.ptr == NULL))
    {
        printf("%p %p %p %p\n", game->texture.n.ptr, game->texture.s.ptr, game->texture.w.ptr, game->texture.e.ptr);
        printf("Error\nInvalid texture path\n");
        return (1);
    }
    return (0);
}

static void free_textures(t_game *game)
{
    if (game->texture.n.ptr)
        mlx_destroy_image(game->mlx, game->texture.n.ptr);
    if (game->texture.s.ptr)
        mlx_destroy_image(game->mlx, game->texture.s.ptr);
    if (game->texture.w.ptr)
        mlx_destroy_image(game->mlx, game->texture.w.ptr);
    if (game->texture.e.ptr)
        mlx_destroy_image(game->mlx, game->texture.e.ptr);
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
    free(map_settings->elmap);
    free(map_settings);
    printf("Textures loaded\n");
    printf("Ceiling color: %d\n", game->texture.ceil_color);
    printf("Floor color: %d\n", game->texture.floor_color);
}