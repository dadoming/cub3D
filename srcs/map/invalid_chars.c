/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:03:10 by dadoming          #+#    #+#             */
/*   Updated: 2023/04/14 19:21:35 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

static int iterate_through_empty_map(char **map, int *i, int *j);

int invalid_chars(char **map)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (map[i])
    {
        while (map[i] != NULL && map[i][j])
        {
            if (iterate_through_empty_map(map, &i, &j))
                continue;
            if (ft_charinside(map[i][j], "10NSWEDXK") == 0)
            {
                printf("Unknown character found! \n");
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static int iterate_through_empty_map(char **map, int *i, int *j)
{
    while (ft_isspace(map[*i][*j]))
        (*j)++;
    if (map[*i][*j] == '\0')
    {
        *j = 0;
        (*i)++;
        return (1);
    }
    return (0);
}
