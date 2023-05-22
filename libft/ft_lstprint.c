/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 20:13:09 by amaria-d          #+#    #+#             */
/*   Updated: 2023/05/22 19:07:59 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *head)
{	
	if (head)
	{
		ft_printf("%s", (head->content));
		while (head->next != NULL)
		{
			head = head->next;
			ft_printf("%s", (head->content));
		}
	}
}

void	intptr_printer(void *pointer)
{
	ft_printf("%s\n", pointer);
}

void	ft_lstprint2(t_list *head)
{
	ft_lstiter(head, intptr_printer);
}
