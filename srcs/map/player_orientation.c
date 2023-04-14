# include "../../includes/cub3D.h"

static void letter_init(t_player_check *l);
static void player_found(char c, t_player_check *l);
static int too_many_player(t_player_check *l);
static int player_orient(t_player_check l);

int get_player_orientation(char **map)
{
    int i;
    int j;
    t_player_check l;

    i = 0;
    j = 0;
    letter_init(&l);
    while (map[i])
    {
        while (map[i][j] != '\0')
        {
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
                player_found(map[i][j], &l);
            j++;
        }
        i++;
        j = 0;
    }
    if (too_many_player(&l))
        return (NONE);
    return (player_orient(l));
}

static void letter_init(t_player_check *l)
{
    l->north = 0;
    l->south = 0;
    l->east = 0;
    l->west = 0;
}

static void player_found(char c, t_player_check *l)
{
    if (c == 'N')
        l->north++;
    if (c == 'S')
        l->south++;
    if (c == 'E')
        l->east++;
    if (c == 'W')
        l->west++;
}

static int too_many_player(t_player_check *l)
{
    if (l->east == 0 && l->north == 0 && l->south == 0 && l->west == 0)
    {
        printf("No player found in map\n");
        return (1);
    }
    else if ((l->east >= 1 && (l->north >= 1 || l->south >= 1 || l->west >= 1)) || \
            (l->north >= 1 && (l->east >= 1 || l->south >= 1 || l->west >= 1)) || \
            (l->south >= 1 && (l->east >= 1 || l->north >= 1 || l->west >= 1)) || \
            (l->west >= 1 && (l->east >= 1 || l->north >= 1 || l->south >= 1)))
    {
        printf("More than one player letter\n");
        return (1);
    }
    return (0);
}

static int player_orient(t_player_check l)
{
    if (l.north == 1)
        return (NORTH);
    else if (l.south == 1)
        return (SOUTH);
    else if (l.east == 1)
        return (EAST);
    else if (l.west == 1)
        return (WEST);
    return (NONE);
}


