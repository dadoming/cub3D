/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:26:38 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/17 16:12:46 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

int check_input(int argc, char **argv)
{
	t_start_values ret;
	
	if (argc == 1)
	{
        fileXtract(select_map());
    }
    else if (argc == 2)
	{
		ret.map_name = ft_strdup(argv[1]);
		ret.mouse_selected = 0;
		fileXtract(ret);
	}
	else
	{
		printf("Wrong number of args");
		exit(0);
	}
	return (0);
	//TODO: ? run_game(settings);
}