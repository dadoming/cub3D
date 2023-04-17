# include "../../includes/cub3D.h"

static void letter_init(t_player_check *l);
static void player_found(char c, t_player_check *l);
static int too_many_player(t_player_check *l, t_plinfo *player);
static void player_pos(t_plinfo *player, int x, int y);
static void player_orient(t_player_check l, t_plinfo *player);

static void player_pos(t_plinfo *player, int x, int y)
{
    player->pos.x = (float)x;
    player->pos.y = (float)y;
}

void get_player(char **map, t_plinfo *player)
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
            if (l.east == 0 && l.north == 0 && l.south == 0 && l.west == 0)
                player_pos(player, i, j); 
            if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
                player_found(map[i][j], &l);
            j++;
        }
        i++;
        j = 0;
    }
    if (too_many_player(&l, player))
        return ;
    player_orient(l, player);
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

static int too_many_player(t_player_check *l, t_plinfo *player)
{
    if (l->east == 0 && l->north == 0 && l->south == 0 && l->west == 0)
    {
        printf("No player found in map\n");
        player->theta = (float)NONE;
        return (1);
    }
    else if ((l->east >= 1 && (l->north >= 1 || l->south >= 1 || l->west >= 1)) || \
            (l->north >= 1 && (l->east >= 1 || l->south >= 1 || l->west >= 1)) || \
            (l->south >= 1 && (l->east >= 1 || l->north >= 1 || l->west >= 1)) || \
            (l->west >= 1 && (l->east >= 1 || l->north >= 1 || l->south >= 1)))
    {
        player->theta = (float)NONE;
        printf("More than one player letter\n");
        printf("%f\n", player->theta);
        return (1);
    }
    return (0);
}

static void player_orient(t_player_check l, t_plinfo *player)
{
    if (l.north == 1)
        player->theta = (float)NORTH; 
    else if (l.south == 1)
        player->theta = (float)SOUTH;
    else if (l.east == 1)
        player->theta = (float)EAST;
    else if (l.west == 1)
        player->theta = (float)WEST;
    else 
        player->theta = (float)NONE;
}


