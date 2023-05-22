/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_notstrpos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:14:34 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 19:14:35 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * This function will not check the last '\0'
 * Remember: pos is not index!
*/
size_t	ft_notstrpos(char *s, char *notstr)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (! ft_charinside(s[i], notstr))
			return (i);
		i++;
	}
	return (0);
}
