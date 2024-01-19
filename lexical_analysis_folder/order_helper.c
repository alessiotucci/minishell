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

// Insert your move_node function here
void move_node(t_list_of_tok **head, t_list_of_tok *target_node, t_list_of_tok *moving_node)
{
	t_list_of_tok *temp = NULL;

	// If the moving node is the head of the list, update the head pointer
	if (*head == moving_node)
		*head = moving_node->next;
	// Disconnect the moving node and all nodes after it from the list
	if (moving_node->previous != NULL)
		moving_node->previous->next = NULL;

	// Find the last node in the moving node's sublist
	temp = moving_node;
	while (temp->next != NULL)
		temp = temp->next;
	// If the target node is the head of the list, move the moving node to the front
	if (*head == target_node)
	{
		temp->next = *head;
		(*head)->previous = temp;
		*head = moving_node;
	}
	else
	{
		// Otherwise, insert the moving node before the target node
		temp->next = target_node;
		moving_node->previous = target_node->previous;
		target_node->previous->next = moving_node;
		target_node->previous = temp;
	}
}


void move_node_fix(t_list_of_tok **head, t_list_of_tok *target_node, t_list_of_tok *moving_node)
{
    //t_list_of_tok *temp = NULL;
    t_list_of_tok *sublist_end = moving_node;

    // Find the end of the sublist starting at moving_node, stopping at redirection or pipe
    while (sublist_end->next && sublist_end->next->type != T_REDIR_OUT && sublist_end->next->type != T_REDIR_IN && sublist_end->next->type != T_REDIR_APP && sublist_end->next->type != T_PIPES)
        sublist_end = sublist_end->next;

    // If the moving node is the head of the list, update the head pointer
    if (*head == moving_node)
        *head = moving_node->next;

    // Disconnect the moving node and all nodes after it from the list
    if (moving_node->previous != NULL)
        moving_node->previous->next = sublist_end->next;
    if (sublist_end->next != NULL)
        sublist_end->next->previous = moving_node->previous;

    // Insert the moving node before the target node
    moving_node->previous = target_node->previous;
    sublist_end->next = target_node;
    if (target_node->previous != NULL)
        target_node->previous->next = moving_node;
    target_node->previous = sublist_end;

    // If the target node was the head of the list, update the head pointer
    if (*head == target_node)
        *head = moving_node;
}

