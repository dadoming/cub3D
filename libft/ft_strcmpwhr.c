/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmpwhr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 19:05:06 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/22 19:05:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Gives pos where the strings diverge
 * Not idx! 0 is wrong: 1 is first ([0])
 * 2 is second ([1]) ...
*/
size_t	ft_strcmpwhr(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (i + 1);
		i++;
	}
	return (i + 1);
}
