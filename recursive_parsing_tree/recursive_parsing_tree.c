/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:44 by atucci            #+#    #+#             */
/*   Updated: 2023/12/15 19:52:37 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_tree_node *create_node(t_list_of_tok *token)
{
	t_tree_node	*node;

	node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (node == NULL)
		exit(2); // YOU should handle the error in a better way than this...
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
static t_tree_node	*create_tree(t_list_of_tok **head)
{
	t_list_of_tok	*high_priority;
	t_list_of_tok	*current;
	t_tree_node		*root;

	if (head == NULL || *head == NULL)
	return (NULL);
	high_priority = *head;
	current = (*head)->next;
	while (current != NULL)
	{
		if (current->priority_lev > high_priority->priority_lev)
			high_priority = current;
		current = current->next;
	}
	if (high_priority == NULL)
	{
		printf("high priority is null\n");
		return (NULL);
	}
	root = create_node(high_priority);
	// Print tabs for each priority level
	for (int i = 0; i < high_priority->priority_lev; i++) // for NORMINETTE!
		printf("\t");
	// Print the highest priority token //
//	if (high_priority->type != T_PARENT)
//	print_node(high_priority);
	printf("%s\n", high_priority->command_as_string);
	if (high_priority->previous != NULL)
	{
		high_priority->previous->next = NULL;
		root->left = create_tree(head);
	}
	if (high_priority->next != NULL)
	{
		high_priority->next->previous = NULL;
		root->right = create_tree(&high_priority->next);
	}
	return (root);
}

void	recursive_tree_builder(t_list_of_tok **head)
{
	t_tree_node	*root;

	root = create_tree(head);
//	print_tree(root, 0);
	parser2();
	parser3();
	return ;
}
