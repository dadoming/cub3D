# include "../includes/cub3D.h"

void	objiter(t_game *game)
{
	int j;
	int i;
	t_object *obj;

	j = 1;
	while (game->objmap[j] != NULL)
	{
		i = 1;
		while (game->objmap[j][i] != NULL)
		{
			obj = game->objmap[j][i];
			if (obj->type == DOOR)
			{
				// printf("Found a door\n");
				update_gun(&((t_door *)obj)->animation);
				((t_door *)obj)->animation.trigger = 1;
			}
			i++;
		}
		j++;
	}
}

void update(t_game *game, microSeconds now)
{
	//TODO(amc): stop update function from calling gettime
	// update will receive the now time and everything should be
	// calculated from that
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	objiter(game);
	// update_dynamite(&game->explosion);
	update_gun(&game->player_shoot);
    draw_weapon(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
}
