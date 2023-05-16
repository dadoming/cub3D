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
			if (obj->type == WALL) //TODO: should be DOOR
			{
				update_gun(&game->capy_idle);
				update_gun(&game->capy_walk);
				game->capy_idle.trigger = 1;
				game->capy_walk.trigger = 1; // constant animate
				//TODO: this code should work but isnt because
				// this func is not iterating on doors
				// for unknown reasons
				// update_gun(((t_door *)obj)->animation);
				// ((t_door *)obj)->animation->trigger = 1;
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
