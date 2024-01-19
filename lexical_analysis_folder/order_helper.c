/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:09 by atucci            #+#    #+#             */
/*   Updated: 2024/01/17 17:24:53 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Helper function to insert a node after a given node */
void	insert_after_node(t_list_of_tok *nod_after, t_list_of_tok *new_node)
{
	if (nod_after == NULL || new_node == NULL)
		return ;
	new_node->next = nod_after->next;
	new_node->previous = nod_after;
	if (nod_after->next != NULL)
		nod_after->next->previous = new_node;
	nod_after->next = new_node;
}

/* Helper function to remove a node from the list */
void	remove_node(t_list_of_tok **head, t_list_of_tok *node_to_remove)
{
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (node_to_remove->previous != NULL)
		node_to_remove->previous->next = node_to_remove->next;
	else
		*head = node_to_remove->next;
	if (node_to_remove->next != NULL)
		node_to_remove->next->previous = node_to_remove->previous;
	node_to_remove->next = NULL;
	node_to_remove->previous = NULL;
}

void	move_node(t_list_of_tok **head, t_list_of_tok *target, t_list_of_tok *moving)
{
	t_list_of_tok	*sublist_end;

	sublist_end = moving;
	while (sublist_end->next && sublist_end->next->type != T_REDIR_OUT && sublist_end->next->type != T_REDIR_IN && sublist_end->next->type != T_REDIR_APP && sublist_end->next->type != T_PIPES)
		sublist_end = sublist_end->next;
	if (*head == moving)
		*head = moving->next;
	if (moving->previous != NULL)
		moving->previous->next = sublist_end->next;
	if (sublist_end->next != NULL)
		sublist_end->next->previous = moving->previous;
	moving->previous = target->previous;
	sublist_end->next = target;
	if (target->previous != NULL)
		target->previous->next = moving;
	target->previous = sublist_end;
	if (*head == target)
		*head = moving;
}
