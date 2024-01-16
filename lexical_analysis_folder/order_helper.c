/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/15 16:11:26 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Helper function to insert a node after a given node
void	insert_after_node(t_list_of_tok *node_to_insert_after, t_list_of_tok *new_node)
{
	if (node_to_insert_after == NULL || new_node == NULL)
		return;
	new_node->next = node_to_insert_after->next;
	new_node->previous = node_to_insert_after;
	if (node_to_insert_after->next != NULL)
		node_to_insert_after->next->previous = new_node;
	node_to_insert_after->next = new_node;
}

// Helper function to remove a node from the list
void	remove_node(t_list_of_tok **head, t_list_of_tok *node_to_remove)
{
	if (*head == NULL || node_to_remove == NULL)
		return;

	if (node_to_remove->previous != NULL)
		node_to_remove->previous->next = node_to_remove->next;
	else
		*head = node_to_remove->next;
	if (node_to_remove->next != NULL)
		node_to_remove->next->previous = node_to_remove->previous;
	node_to_remove->next = NULL;
	node_to_remove->previous = NULL;
}

