# include "../includes/cub3D.h"

void	objiter(t_game *game, microSeconds tmstmpnow)
{
	int j;
	int i;
	t_object *obj;

	j = 1;
	while (game->charmap[j])
	{
		i = 1;
		while (game->charmap[j][i])
		{
			obj = game->objmap[j][i];
			if (obj)
			{
				if (obj->type == DOOR)
				{
					// printf("Found a door\n");
					update_anim(&((t_door *)obj)->animation, tmstmpnow);
					((t_door *)obj)->animation.trigger = 1;
				}
				else if (obj->type == STATICENEMY)
				{
					// printf("Found a staticenemy\n");
					update_anim(&((t_staticenemy *)obj)->animation, tmstmpnow);
					((t_staticenemy *)obj)->animation.trigger = 1;
				}
			}
			i++;
		}
		j++;
	}
}

void update(t_game *game, microSeconds tmstmpnow)
{
	if (game->minimap_toggle == 0)
		draw_minimap(game);
	objiter(game, tmstmpnow);

	update_anim(&game->player_shoot, tmstmpnow);

	draw_weapon(game);
	draw_crosshair(game, 5, rgbtocolor(153, 0, 153));
}
