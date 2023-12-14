/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_parsing_tree.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:14:44 by atucci            #+#    #+#             */
/*   Updated: 2023/12/14 17:47:20 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static t_tree_node	*create_tree(t_list_of_tok *head)
{
	t_tree_node *root;
	t_list_of_tok *current;
	int max_priority;
	printf("creating a nice tree\n\n");
	max_priority = 0;
	root = NULL;
	current = head;
	// Find the command with the highest priority
	while (current != NULL)
	{
//		if (current->priority_lev > max_priority)
//		{
//			max_priority = current->priority_lev;
//			root = create_tree(current);
//		}
		current = current->next;
	}
	// Recursively create subtrees for commands inside parentheses
	current = head;
	while (current != NULL)
	{
//		if (current->priority_lev == max_priority)
//		{
//			root->left = create_tree(head);
//			root->right = create_tree(current->next);
//			break;
//		}
		current = current->next;
	}
	return root;
}

void	recursive_tree_builder(t_list_of_tok **head)
{
	create_tree(*head);
	parser1();
	parser2();
	parser3();
	return ;
}
