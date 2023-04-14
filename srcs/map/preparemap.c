/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:41:46 by dadoming          #+#    #+#             */
/*   Updated: 2023/04/14 19:41:07 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static int get_top(char **map, int y, int x)
{
    while (map[y])
    {
        if (map[y][x] == '1')
            return (y);
        while (map[y][x])
        {
            if (map[y][x] == '1')
                return (y);
            x++;
        }
        x = 0;
        y++;
    }
    return (0);
}

static int get_bottom(char **map, int y, int x)
{
    while (y >= 0 && map[y])
    {
        if (map[y][x] == '1')
            return (y);
        while (map[y][x])
        {
            if (map[y][x] == '1')
                return (y);
            x++;
        }
        x = 0;
        y--;
    }
    return (0);
}

static int get_left(char **map, int y, int x)
{
    int max;
    
    max = ft_mtrxlen((void**)) - 1map;
    while (map[y])
    {
        if (map[y][x] == '1')
            return (x);
        while (map[y][x] && y < max)
        {
            if (map[y][x] == '1')
                return (x);
            y++;
        }
        y = 0;
        x++;
    }
    return (0);
}

static int get_right(char **map, int y, int x)
{
    int last;

    last = 0;
    while (map[y])
    {
        if (map[y][x] == '1' && x > last)
            last = x;
        while (map[y][x])
        {
            if (map[y][x] == '1' && x > last)
                last = x;
            x++;
        }
        x = 0;
        y++;
    }
    return (last);
}

static void get_maximum_values(t_map_check *maxs, char **map)
{
    maxs->top = get_top(map, 0, 0);
    maxs->bottom = get_bottom(map, ft_mtrxlen((void**) map) - 1, 0);
    maxs->right = get_right(map, 0, 0);
    maxs->left = get_left(map, 0, 0);
    
    printf("top: %d, bottom: %d, right: %d, left: %d\n", 
        maxs->top, maxs->bottom, maxs->right, maxs->left);
}

char **cut_and_define_border(char **map)
{
   // char **new_map;
    t_map_check maxs;

    get_maximum_values(&maxs, map);
    
    return (NULL);
    //charmapFree(map);
    //return (new_map);
}

int prepare_map(t_settings *map_settings)
{
    int player_orientation;

    player_orientation = NONE;
    if (invalid_chars(map_settings->charmap))
    {
        free_on_invalid(map_settings);
        exit(0);
    }

    map_settings->charmap = cut_and_define_border(map_settings->charmap);

    //player_orientation = get_player_orientation(map_settings->charmap);
    //if (player_orientation == NONE)
    //{
    //    free_on_invalid(map_settings);
    //    printf("Exiting program...\n");
    //    exit(0);
    //}
    
    return (player_orientation);
}
