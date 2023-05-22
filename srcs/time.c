/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:32:50 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/19 00:44:53 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

/**
 * Converts clock to microseconds
*/
t_microseconds	timestamp(struct timespec clock)
{
	return (clock.tv_sec * 1000000 + clock.tv_nsec / 1000);
}

t_microseconds	timediff(struct timespec old)
{
	struct timespec	now;

	clock_gettime(CLOCK_MONOTONIC, &now);
	return (timestamp(now) - timestamp(old));
}

t_microseconds	timestampdiff(struct timespec new, struct timespec old)
{
	return (timestamp(new) - timestamp(old));
}
