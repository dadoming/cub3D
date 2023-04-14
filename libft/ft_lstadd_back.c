/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:29:20 by amaria-d          #+#    #+#             */
/*   Updated: 2023/04/12 16:04:50 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, char *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = ft_lstnew(new);
		return ;
	}
	ft_lstlast(*lst)->next = ft_lstnew(new);
}

/*
int main()
{
	t_list	*head;
	t_list	el[2];

	head = NULL;

	el[0].content = (void *)"good";
	el[0].next = el[1];

	el[1].content = (void *)"bye";
	el[1].next

	// printf("%d\n", ft_lstsize(head)); // == 0

	head = ft_lstnew((void *)"hello");
	// printf("%d\n", ft_lstsize(head)); // == 1

	ft_lstadd_back(&head, &(el[0]));
	// printf("%d\n", ft_lstsize(head)); // == 2

	ft_lstprint(head);

	return 0;
}
*/
