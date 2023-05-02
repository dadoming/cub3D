# include "../includes/cub3D.h"

void door_action(t_game *game, int x, int y)
{
	int i = 0;
	while (i < game->door_count)
	{
		if (abs(game->door[i].x - x) == 1 && abs(game->door[i].y - y) == 0)
		{
			if (game->door[i].state == 0)
				game->door[i].state = 1;
			else
				game->door[i].state = 0;
		}
		else if (abs(game->door[i].x - x) == 0 && abs(game->door[i].y - y) == 1)
		{
			if (game->door[i].state == 0)
				game->door[i].state = 1;
			else
				game->door[i].state = 0;
		}
		i++;
	}
}


int this_door_open(t_game *game, int x, int y)
{
	int i;

	i = 0;
	while (i < game->door_count)
    {
		if (abs(game->door[i].x - y) <= 1 && abs(game->door[i].y - x) == 0)
		{
			return (game->door[i].state);
		}
		else if (abs(game->door[i].y - x) == 0 && abs(game->door[i].x - y) <= 1)
		{
			return (game->door[i].state);
		}
		i++;
	}
	return (0);
}

int get_number_doors(char **map)
{
	int i;
	int j;
	int nmbr_doors;

	i = 0;
	j = 0;
	nmbr_doors = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == 'D')
				nmbr_doors++;
			j++;
		}
		j = 0;
		i++;
	}
	return (nmbr_doors);
}

static void init(t_game *game)
{
    int i;
    int j;
    int nmbr_doors;

    i = 0;
    j = 0;
    nmbr_doors = 0;
    while (game->charmap[i])
	{
		while (game->charmap[i][j])
		{
			if (game->charmap[i][j] == 'D')
			{
				game->door[nmbr_doors].x = j;
				game->door[nmbr_doors].y = i;
				game->door[nmbr_doors].state = 0;
                nmbr_doors++;
			}
			j++;
		}
		j = 0;
		i++;
    }
}

void init_doors(t_game *game)
{
	game->door_count = get_number_doors(game->charmap);
	if (game->door_count == 0)
	{
		game->door = NULL;
		return ;
	}
	game->door = malloc(sizeof(t_door) * game->door_count);
    init(game);
}