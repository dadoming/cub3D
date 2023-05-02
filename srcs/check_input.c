/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:26:38 by dadoming          #+#    #+#             */
/*   Updated: 2023/04/18 17:24:00 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

int check_input(int argc, char **argv)
{
    if (argc == 1)
    {
        fileXtract("maps/5_works_small.cub");
		// fileXtract("maps/")
    }
	else if (argc == 2)
	{
		fileXtract(argv[1]);
	}
	else
	{
		printf("Wrong number of args");
		exit(0);
	}
	return (0);
	//TODO: ? run_game(settings);
}