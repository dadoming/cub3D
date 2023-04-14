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

int map_playable(char **map);
static int check_surrounding(char **map, int i, int j);

int prepare_map(t_settings *map_settings)
{
    int player_orientation;

    player_orientation = NONE;
    if (invalid_chars(map_settings->charmap))
        free_on_invalid(map_settings);
    map_settings->charmap = cut_and_define_border(map_settings->charmap);
    if (map_settings->charmap == NULL)
        free_on_invalid(map_settings);
    if (map_playable(map_settings->charmap))
        free_on_invalid(map_settings);
    player_orientation = get_player_orientation(map_settings->charmap);
    if (player_orientation == NONE)
        free_on_invalid(map_settings);
    return (player_orientation);
}

static int check_surrounding(char **map, int i, int j)
{
    if (map[i - 1][j] == '2')
        return (1);
    if (map[i + 1][j] == '2')
        return (1);
    if (map[i][j - 1] == '2')
        return (1);
    if (map[i][j + 1] == '2')
        return (1);
    return (0);
}

int map_playable(char **map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i][j] != '\0')
        {
            if (map[i][j] == '0' || map[i][j] == 'D')
            {
                if (check_surrounding(map, i, j))
                {
                    printf("Map is open\n");
                    return (1);
                }
            }
            j++;
        }
        i++;
        j = 0;
    }
    return (0);
}


