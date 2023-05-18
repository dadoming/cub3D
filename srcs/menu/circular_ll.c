/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circular_ll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:15:49 by dadoming          #+#    #+#             */
/*   Updated: 2023/05/18 21:16:22 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/menu.h"

t_map_list	*create_node(char *name)
{
	t_map_list	*node;

	node = malloc(sizeof(t_map_list));
	if (!node)
		return (NULL);
	node->name = name;
	node->next = node;
	node->prev = node;
	return (node);
}

void	insert_at_beggining(t_map_list **head, t_map_list *node)
{
	if (!head || !node)
		return ;
	node->next = *head;
	node->prev = (*head)->prev;
	(*head)->prev->next = node;
	(*head)->prev = node;
	*head = node;
}

void	insert_at_end(t_map_list **head, t_map_list *node)
{
	t_map_list	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = (*head)->prev;
	tmp->next = node;
	node->prev = tmp;
	node->next = *head;
	(*head)->prev = node;
}

void	delete_node(t_map_list **head, t_map_list *node)
{
	if (!head || !node)
		return ;
	if (*head == node)
		*head = node->next;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	if (node->name)
		free(node->name);
	free(node);
}

void	delete_circular_list(t_map_list **head)
{
	t_map_list	*current;
	t_map_list	*tmp;

	if (!head || !*head)
		return ;
	current = *head;
	while (current->next != *head)
	{
		tmp = current;
		current = current->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
	}
	if (current->name)
		free(current->name);
	free(current);
	*head = NULL;
}
