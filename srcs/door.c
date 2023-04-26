# include "../includes/cub3D.h"

int this_door_open(t_game *game, int x, int y)
{
	int i;

	i = 0;
	while (i < game->door_count)
	{
		printf("door %d = %d %d\nplayer =   %d %d\n", i, game->door[i].x, game->door[i].y, x / SQUARESIZE, y/ SQUARESIZE);
		if (abs(game->door[i].x - x / SQUARESIZE) <= 1 && abs(game->door[i].y - y / SQUARESIZE) == 0)
		{
			printf("door %d state: %d\n", i, game->door[i].state);
			return (game->door[i].state);
		}
		else if (abs(game->door[i].x - x) == 0 && abs(game->door[i].y - y) <= 1)
		{
			printf("door %d state: %d\n", i, game->door[i].state);
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
	int i;
	int j;

	i = 0;
	j = 0;
	game->door_count = get_number_doors(game->charmap);
	if (game->door_count == 0)
	{
		game->door = NULL;
		return ;
	}
	game->door = malloc(sizeof(t_door) * game->door_count);
    init(game);
}