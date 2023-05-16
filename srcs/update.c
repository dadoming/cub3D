# include "../includes/cub3D.h"

void	objiter(t_game *game)
{
	int j;
	int i;
	t_object *obj;

	j = 1;
	while (game->objmap[j])
	{
		i = 1;
		while (game->objmap[j][i] && game->objmap[j][i]->type != 0)
		{
			obj = game->objmap[j][i];
			//TODO(amc): do stuff
			if (obj->type == WALL)
			{
				update_gun(&game->door_idle);
				game->door_idle.trigger = 1; // constant animate
			}
			i++;
		}
		j++;
	}
}

void update(t_game *game, microSeconds now)
{
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	objiter(game);
	// update_dynamite(&game->explosion);
	update_gun(&game->player_shoot);
    draw_weapon(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
}
