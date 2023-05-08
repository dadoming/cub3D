# include "../../includes/cub3D.h"

void	draw_ray(t_game *game)
{
    t_raycast ray;

    ray.x = 0;
    while (ray.x < WINDOWSIZE_X)
    {
        ray_direction(&ray, game, ray.x);
        delta_dist(&ray);
        perp_wall_dist(&ray, game);
        line_height(&ray);
        get_draw_start_end(&ray);
        wall_texture_position(&ray, game);
        object_selector(game, &ray);
        draw_vertical_stripe(game, &ray);
        ray.x++;
    }
}

void object_selector(t_game *game, t_raycast *ray)
{
    if (game->objmap[ray->mapX][ray->mapY] == NULL)
        return ;
    if (ray->x == (WINDOWSIZE_X / 2))
        game->select = game->objmap[ray->mapX][ray->mapY];
}



